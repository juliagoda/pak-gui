#include "mainwindowview.h"

#include "availablepackagescolumn.h"
#include "installedpackagescolumn.h"
#include "qnamespace.h"
#include "statisticscommandparser.h"
#include "updatedpackagescolumn.h"
#include "installcommandparser.h"
#include "packagesearch.h"
#include "statistics.h"
#include "process.h"
#include "packagedownloader.h"
#include "previewdesign.h"
#include "logger.h"
#include "timeconverter.h"
#include "settings.h"

#include <KLocalizedString>
#include <KLed>
#include <QCheckBox>
#include <QScopedPointer>
#include <QPushButton>
#include <QProcess>
#include <QPointer>
#include <QScopedPointer>
#include <QObject>
#include <QVariant>
#include <KMainWindow>
#include <QChartView>
#include <QPieSeries>
#include <QTimer>
#include <QDateTime>
#include <QtConcurrent/QtConcurrent>


MainWindowView::MainWindowView(QWidget *parent)
    : QWidget(parent),
      spinning_animation(new SpinningAnimation),
      generated_previews_map(QMap<Process::Task, QPointer<QWidget>>()),
      progress_view(QSharedPointer<ProgressView>(new ProgressView)),
      process(nullptr),
      actions_access_checker(nullptr),
      internet_connection_timer(new QTimer(this)),
      is_operation_running(false)
{
    m_ui.setupUi(this);
    m_ui.aur_led_label->setToolTip(i18n("Internet connection state and auracle-git package presence"));
    m_ui.polaur_led_label->setToolTip(i18n("Internet connection state and git package presence"));
    m_ui.repo_led_label->setToolTip(i18n("Internet connection state"));
}


void MainWindowView::setProcess(QSharedPointer<Process> new_process)
{
    process = new_process;
}


void MainWindowView::setActionsAccessChecker(QSharedPointer<ActionsAccessChecker> new_actions_access_checker)
{
    actions_access_checker = new_actions_access_checker;
}

void MainWindowView::init()
{
    initColumns();
    initSignals();
    hideWidgets();
    startInternetCheckTimer();
    startPackagesCheckTimer();
    startAnimations();
}


void MainWindowView::run()
{
    QThread* available_packages_thread(new QThread);
    QThread* installed_packages_thread(new QThread);

    m_ui.available_packages_list->hide();
    m_ui.installed_packages_list->hide();
    m_ui.search_available_packages_checkbox->setEnabled(false);
    m_ui.search_installed_packages_checkbox->setEnabled(false);

    QObject::connect(available_packages_thread, &QThread::started, this, [this]() { available_packages_column->fill(); emit availablePackagesFillEnded(); });
    QObject::connect(installed_packages_thread, &QThread::started, this, [this]() { installed_packages_column->fill(); emit installedPackagesFillEnded(); });
    QObject::connect(available_packages_column.get(), &AvailablePackagesColumn::startOtherThreads, this, [this]()
    {
        emit startOtherThreads();
    });

    QObject::connect(available_packages_thread, &QThread::finished, available_packages_thread, &QThread::deleteLater);
    QObject::connect(installed_packages_thread, &QThread::finished, installed_packages_thread,  &QThread::deleteLater);
    installed_packages_thread->start(QThread::TimeCriticalPriority);
    available_packages_thread->start(QThread::TimeCriticalPriority);
    checkUpdates();
}


void MainWindowView::hideWidgets()
{
    m_ui.installed_preview_area->hide();
    m_ui.progress_view_checkbox->hide();
    m_ui.sort_installed_packages->hide();
    m_ui.search_installed_packages_lineedit->hide();
    m_ui.installed_packages_list->hide();
    hideWidgetsExceptInstalled();
}


void MainWindowView::hideWidgetsExceptInstalled()
{
    m_ui.updated_preview_area->hide();
    m_ui.available_preview_area->hide();
    m_ui.sort_available_packages->hide();
    m_ui.sort_packages_to_update->hide();
    m_ui.search_packages_to_update_lineedit->hide();
    m_ui.search_available_packages_lineedit->hide();
    m_ui.available_packages_list->hide();
    m_ui.packages_to_update_list->hide();
}


void MainWindowView::startInternetCheckTimer()
{
    if (internet_connection_timer.isNull() || actions_access_checker.isNull())
        return;

    disconnect(internet_connection_timer, &QTimer::timeout, actions_access_checker.get(), &ActionsAccessChecker::checkInternetConnection);
    if (Settings::records()->internetReconnectionTimeMinutes() == 0)
        return;

    connect(internet_connection_timer, &QTimer::timeout, actions_access_checker.get(), &ActionsAccessChecker::checkInternetConnection);
    int milliseconds = TimeConverter::minutesToMilliseconds(Settings::records()->internetReconnectionTimeMinutes());
    internet_connection_timer->start(milliseconds);
    Logger::logger()->logDebug(QStringLiteral("Internet connection checker started with interval %2").arg(milliseconds));
}


void MainWindowView::showFinishInformation()
{
    QMessageBox::information(this, i18n("All processes ended"), i18n("All processes have been completed."));
}


void MainWindowView::startPackagesCheckTimer()
{
    if (actions_access_checker.isNull())
        return;

    QPointer<QTimer> packages_timer = new QTimer(this);
    connect(packages_timer, &QTimer::timeout, actions_access_checker.get(), &ActionsAccessChecker::checkRequiredPackages);
    packages_timer->start(8000);
    Logger::logger()->logDebug(QStringLiteral("Required packages checker started with interval %2").arg(8000));
}


void MainWindowView::initSignals()
{
    QObject::connect(this, &MainWindowView::availablePackagesFillEnded, this, &MainWindowView::connectSignalsForAvailablePackages);
    QObject::connect(this, &MainWindowView::installedPackagesFillEnded, this, &MainWindowView::connectSignalsForInstalledPackages);
    QObject::connect(this, &MainWindowView::packagesToUpdateFillEnded, this, &MainWindowView::connectSignalsForUpdatedPackages);

    QObject::connect(m_ui.console_view_install, &QCheckBox::toggled, this, [this](bool is_checked) { if (is_checked) m_ui.available_preview_area->show(); else m_ui.available_preview_area->hide(); });
    QObject::connect(m_ui.console_view_uninstall, &QCheckBox::toggled, this, [this](bool is_checked) { if (is_checked) m_ui.installed_preview_area->show(); else m_ui.installed_preview_area->hide(); });
    QObject::connect(m_ui.console_view_update, &QCheckBox::toggled, this, [this](bool is_checked) { if (is_checked) m_ui.updated_preview_area->show(); else m_ui.updated_preview_area->hide(); });

    emit initStarted();
    Logger::logger()->logInfo("Initialization started");

    QObject::connect(updated_packages_column.get(), &UpdatedPackagesColumn::currentPackagesCountChanged, this, [this](int packages_count){ emit packagesToUpdateCountChanged(packages_count); });

    if (!actions_access_checker.isNull())
    {
        QObject::connect(actions_access_checker.get(), &ActionsAccessChecker::internetAccessChanged, this, &MainWindowView::toggleWidgetsAccess);
        QObject::connect(actions_access_checker.get(), &ActionsAccessChecker::auracleAccessChanged, [this](bool is_auracle_installed){ is_auracle_installed && actions_access_checker->isOnline() ? m_ui.aur_kled->on() : m_ui.aur_kled->off();});
        QObject::connect(actions_access_checker.get(), &ActionsAccessChecker::gitAccessChanged, this, [this](bool is_git_installed){ is_git_installed && actions_access_checker->isOnline() ? m_ui.polaur_kled->on() : m_ui.polaur_kled->off();});
    }

    QObject::connect(this, &MainWindowView::operationsAmountIncreased, m_ui.progress_view_checkbox, &QCheckBox::show);

    if (!progress_view.isNull())
        QObject::connect(progress_view.data(), &QDialog::rejected, this, [this](){ m_ui.progress_view_checkbox->setChecked(false); });

    QObject::connect(m_ui.progress_view_checkbox, &QCheckBox::toggled, this, [this](bool is_checked) { if (is_checked) { progress_view->resize(500, 500); progress_view.data()->show(); } else progress_view.data()->hide(); });
    QObject::connect(m_ui.check_all_updates_checkbox, &QCheckBox::toggled, updated_packages_column.get(), &UpdatedPackagesColumn::toggleAllPackages);

    if (process.isNull())
        return;

    QObject::connect(process.data(), &Process::generatedOutput, this, &MainWindowView::generateOutput, Qt::AutoConnection);
    QObject::connect(process.data(), &Process::acceptedTask, this, &MainWindowView::generatePreview);
    QObject::connect(process.data(), &Process::acceptedTask, this, [this](){ spinning_animation->startSmallOnWidget(m_ui.actions_spinning_animation_label);  });
    QObject::connect(process.data(), &Process::finished, this, [this](Process::Task task, int exit_code, QProcess::ExitStatus exit_status) { finishProcess(task, exit_code, exit_status); }, Qt::AutoConnection);
    QObject::connect(process.data(), &Process::finished, this, [this](){ spinning_animation->stopSmallOnWidget(m_ui.actions_spinning_animation_label);  });
}


void MainWindowView::preparePreviews()
{
    updatePreviewsDesign();
    generated_previews_map.insert(Process::Task::Install, m_ui.installed_preview_area);
    generated_previews_map.insert(Process::Task::Uninstall, m_ui.updated_preview_area);
    generated_previews_map.insert(Process::Task::Update, m_ui.available_preview_area);
}


void MainWindowView::updatePreviewsDesign()
{
    PreviewDesign::update(m_ui.text_browser_tab_uninstall);
    PreviewDesign::update(m_ui.text_browser_tab_install);
    PreviewDesign::update(m_ui.text_browser_tab_update);
}


void MainWindowView::initColumns()
{
    available_packages_column = QSharedPointer<AvailablePackagesColumn>(new AvailablePackagesColumn(m_ui.available_packages_list, m_ui.search_available_packages_lineedit, this), &QObject::deleteLater);
    installed_packages_column = QSharedPointer<InstalledPackagesColumn>(new InstalledPackagesColumn(m_ui.installed_packages_list, m_ui.search_installed_packages_lineedit, this), &QObject::deleteLater);
    updated_packages_column = QSharedPointer<UpdatedPackagesColumn>(new UpdatedPackagesColumn(m_ui.packages_to_update_list, m_ui.search_packages_to_update_lineedit, this), &QObject::deleteLater);

    QObject::connect(m_ui.sort_available_packages, &QCheckBox::toggled, available_packages_column.data(), &AvailablePackagesColumn::sort, Qt::AutoConnection);
    QObject::connect(available_packages_column.data(), &AvailablePackagesColumn::checkedPackagesCounterChanged, this, [this](bool has_checked_buttons) { m_ui.install_packages_button->setEnabled(has_checked_buttons); });
    QObject::connect(m_ui.install_packages_button, &QPushButton::clicked, this, [this]() { m_ui.text_browser_tab_install->clear(); process->run(Process::Task::Install, available_packages_column.data()->getCheckedPackagesStringList()); }, Qt::AutoConnection);
    QObject::connect(m_ui.installed_packages_list->model(), &QAbstractListModel::rowsRemoved, this, [this](){ if (m_ui.installed_packages_list->count() == 0) m_ui.uninstall_packages_button->setEnabled(false); }, Qt::AutoConnection);

    QObject::connect(m_ui.sort_installed_packages, &QCheckBox::toggled, installed_packages_column.data(), &InstalledPackagesColumn::sort, Qt::AutoConnection);
    QObject::connect(installed_packages_column.data(), &InstalledPackagesColumn::checkedPackagesCounterChanged, this, [this](bool has_checked_buttons) { m_ui.uninstall_packages_button->setEnabled(has_checked_buttons); }, Qt::AutoConnection);
    QObject::connect(m_ui.uninstall_packages_button, &QPushButton::clicked, this, [this]() { m_ui.text_browser_tab_uninstall->clear(); process->run(Process::Task::Uninstall, installed_packages_column.data()->getCheckedPackagesStringList()); }, Qt::AutoConnection);
    QObject::connect(m_ui.available_packages_list->model(), &QAbstractListModel::rowsRemoved, this, [this](){ if (m_ui.available_packages_list->count() == 0) m_ui.install_packages_button->setEnabled(false); }, Qt::AutoConnection);

    QObject::connect(m_ui.sort_packages_to_update, &QCheckBox::toggled, updated_packages_column.data(), &UpdatedPackagesColumn::sort, Qt::AutoConnection);
    QObject::connect(updated_packages_column.data(), &UpdatedPackagesColumn::checkedPackagesCounterChanged, this, [this](bool has_checked_buttons) { m_ui.update_packages_button->setEnabled(has_checked_buttons); }, Qt::AutoConnection);
    QObject::connect(m_ui.update_packages_button, &QPushButton::clicked, this, [this]() { updated_packages_column.data()->prepareBeforeProcessRun(); }, Qt::AutoConnection);
    QObject::connect(updated_packages_column.data(), &UpdatedPackagesColumn::preparedList, this, [this](QStringList packages_list, Process::Task task){ m_ui.text_browser_tab_update->clear(); process->run(task, packages_list); });
    QObject::connect(m_ui.packages_to_update_list->model(), &QAbstractListModel::rowsRemoved, this, [this](){ if (m_ui.packages_to_update_list->count() == 0) m_ui.update_packages_button->setEnabled(false); }, Qt::AutoConnection);

    QObject::connect(m_ui.installed_packages_list->model(), &QAbstractListModel::rowsInserted, this, [this](){ m_ui.search_installed_packages_checkbox->setEnabled(true); }, Qt::AutoConnection);
    QObject::connect(m_ui.installed_packages_list->model(), &QAbstractListModel::rowsRemoved, this, [this](){ if (m_ui.installed_packages_list->count() == 0) m_ui.search_installed_packages_checkbox->setEnabled(false); }, Qt::AutoConnection);

    QObject::connect(m_ui.available_packages_list->model(), &QAbstractListModel::rowsInserted, this, [this](){ m_ui.search_available_packages_checkbox->setEnabled(true); }, Qt::AutoConnection);
    QObject::connect(m_ui.available_packages_list->model(), &QAbstractListModel::rowsRemoved, this, [this](){ if (m_ui.available_packages_list->count() == 0) m_ui.search_available_packages_checkbox->setEnabled(false); }, Qt::AutoConnection);

    QObject::connect(m_ui.packages_to_update_list->model(), &QAbstractListModel::rowsInserted, this, [this](){ m_ui.search_packages_to_update_checkbox->setEnabled(true); }, Qt::AutoConnection);
    QObject::connect(m_ui.packages_to_update_list->model(), &QAbstractListModel::rowsRemoved, this, [this](){ if (m_ui.packages_to_update_list->count() == 0) m_ui.search_packages_to_update_checkbox->setEnabled(false); }, Qt::AutoConnection);
    QObject::connect(m_ui.packages_to_update_list->model(), &QAbstractListModel::rowsInserted, this, [this](){ m_ui.check_all_updates_checkbox->setEnabled(true); }, Qt::AutoConnection);
    QObject::connect(m_ui.packages_to_update_list->model(), &QAbstractListModel::rowsRemoved, this, [this](){ if (m_ui.packages_to_update_list->count() == 0) m_ui.check_all_updates_checkbox->setEnabled(false); }, Qt::AutoConnection);
}


void MainWindowView::toggleWidgetsAccess(bool is_online)
{
    static bool is_connection_state_not_different = true;
    if (is_connection_state_not_different == is_online)
        return;

    is_connection_state_not_different = is_online;

    if (is_online)
    {
        m_ui.repos_kled->on();
        m_ui.packages_to_update_label->setText(i18n("TO UPDATE"));
        m_ui.accessible_packages->setText(i18n("AVAILABLE TO INSTALL"));
        refresh();
        return;
    }

    Logger::logger()->logInfo(QStringLiteral("Disabling widgets accordingly to offline state"));
    is_online ? m_ui.repos_kled->on() : m_ui.repos_kled->off();
    m_ui.packages_to_update_label->setStyleSheet("color: black; font-size: 15px;");
    m_ui.packages_to_update_label->setText(i18n("No internet connection"));
    m_ui.accessible_packages->setStyleSheet("color: black; font-size: 15px;");
    m_ui.accessible_packages->setText(i18n("No internet connection"));
    m_ui.update_spinning_widget->hide();
    m_ui.installation_spinning_widget->hide();
    emit hideOnlineActions();
    hideWidgetsExceptInstalled();
}


void MainWindowView::connectSignalsForAvailablePackages()
{
    if (m_ui.available_packages_list->count() > 0)
        m_ui.available_packages_list->show();

    if (m_ui.available_packages_list->count() == 0)
    {
        m_ui.accessible_packages->setStyleSheet("color: black; font-size: 15px;");
        m_ui.accessible_packages->setText(i18n("Something went wrong. Try to refresh"));
    }

    m_ui.installation_spinning_widget->hide();
    checkSpinningVisibility();
}


void MainWindowView::connectSignalsForInstalledPackages()
{
    if (m_ui.installed_packages_list->count() > 0)
        m_ui.installed_packages_list->show();

    if (m_ui.installed_packages_list->count() == 0)
    {
        m_ui.installed_packages_label->setStyleSheet("color: black; font-size: 15px;");
        m_ui.installed_packages_label->setText(i18n("Something went wrong. Try to refresh"));
    }

    m_ui.remove_spinning_widget->hide();
    checkSpinningVisibility();
}


void MainWindowView::connectSignalsForUpdatedPackages()
{

    if (m_ui.packages_to_update_list->count() > 0)
        m_ui.packages_to_update_list->show();

    if (m_ui.packages_to_update_list->count() == 0 && (actions_access_checker.isNull() || !actions_access_checker->isOnline()))
    {
        m_ui.packages_to_update_label->setStyleSheet("color: black; font-size: 15px;");
        m_ui.packages_to_update_label->setText(i18n("Cannot be updated - try to refresh"));
    }

    if (m_ui.packages_to_update_list->count() == 0 && !actions_access_checker.isNull() && actions_access_checker->isOnline())
    {
        m_ui.packages_to_update_label->setStyleSheet("color: black; font-size: 15px;");
        m_ui.packages_to_update_label->setText(i18n("There aren't packages to update"));
    }

    m_ui.update_spinning_widget->hide();
    checkSpinningVisibility();
}


void MainWindowView::checkSpinningVisibility()
{
    if (m_ui.update_spinning_widget->isHidden() &&
        m_ui.remove_spinning_widget->isHidden() &&
        m_ui.installation_spinning_widget->isHidden() &&
        actions_access_checker->isOnline())
    {
        emit initEnded();
        is_operation_running = false;
        spinning_animation->stopOnMainWidgets(m_ui.installation_spinning_label,
                                              m_ui.remove_spinning_label,
                                              m_ui.update_spinning_label);
        Logger::logger()->logInfo(QStringLiteral("Refresh/initialization ended"));
    }
}


void MainWindowView::generatePreview(Process::Task task)
{
    QWidget* operation_preview = new QWidget;
    operation_preview->setObjectName(QVariant::fromValue(task).toString());
    QVBoxLayout* vertical_layout = new QVBoxLayout(operation_preview);
    QScrollArea* scroll_area = new QScrollArea(operation_preview);
    scroll_area->setWidgetResizable(true);
    QWidget* scroll_area_widget_contents = new QWidget();
    scroll_area_widget_contents->setGeometry(QRect(0, 0, 358, 200));
    QVBoxLayout* vertical_layout2 = new QVBoxLayout(scroll_area_widget_contents);
    QTextBrowser* text_browser_tab = new QTextBrowser(scroll_area_widget_contents);
    PreviewDesign::update(text_browser_tab);
    text_browser_tab->setObjectName(QString("text_browser_tab_%1").arg(QVariant::fromValue(task).toString().toLower()));

    vertical_layout2->addWidget(text_browser_tab);
    scroll_area->setWidget(scroll_area_widget_contents);
    vertical_layout->addWidget(scroll_area);
    generated_previews_map.insert(task, operation_preview);
    progress_view.data()->addProgressView(operation_preview);

    emit operationsAmountIncreased();
}


void MainWindowView::showStatisticsWindow()
{
    QScopedPointer<StatisticsCommandParser> command_parser(new StatisticsCommandParser);
    auto list_result = command_parser.data()->retrieveInfo();
    auto map_result = command_parser.data()->convertToMap(list_result);

    QPointer<Statistics> statistics = new Statistics(map_result, this);
    statistics->resize(800, 800);
    statistics->show();
}


void MainWindowView::downloadPackage()
{
    QSharedPointer<DownloadCommandParser> download_command_parser(new DownloadCommandParser(QString(), this), &QObject::deleteLater);
    QPointer<DownloaderWindow> automatic_installation(new AutomaticInstallation(download_command_parser, this));
    QPointer<DownloaderWindow> package_input(new PackageInput(download_command_parser));
    QPointer<DownloaderWindow> paths_choice_input(new PathsChoiceInput(download_command_parser));
    QPointer<DownloaderWindow> repos_choice_input(new ReposChoiceInput(download_command_parser));

    automatic_installation->setNext(package_input)->setNext(paths_choice_input)->setNext(repos_choice_input);
    automatic_installation->handle();
}


void MainWindowView::searchPackage()
{
    QSharedPointer<InstallCommandParser> search_command_parser(new InstallCommandParser(), &QObject::deleteLater);
    QPointer<SearchWindow> package_input(new PackageSearchInput(search_command_parser));
    QPointer<SearchWindow> search_results_list(new SearchResultsList(search_command_parser, process));

    package_input->setNext(search_results_list);
    package_input->handle();
}


void MainWindowView::generateOutput(Process::Task task, const QString& line)
{
    switch(task)
    {
    case Process::Task::Install:
        m_ui.text_browser_tab_install->append(line);
        break;

    case Process::Task::Update:
    case Process::Task::UpdateAll:
        m_ui.text_browser_tab_update->append(line);
        break;

    case Process::Task::Uninstall:
        m_ui.text_browser_tab_uninstall->append(line);
        break;

    default:
        generated_previews_map.value(task)->findChild<QTextBrowser*>(QString("text_browser_tab_%1").arg(QVariant::fromValue(task).toString().toLower()))->append(line);
        break;
    }
}


void MainWindowView::finishProcess(Process::Task task, int exit_code, QProcess::ExitStatus exit_status)
{
    Q_UNUSED(exit_code)
    Q_UNUSED(exit_status)

    if (task != Process::Task::Install &&
        task != Process::Task::Update &&
        task != Process::Task::Uninstall &&
        task != Process::Task::UpdateAll)
    {
        progress_view.data()->removeProgressView(generated_previews_map.value(task));
        generated_previews_map.remove(task);
        if (progress_view.data()->tabsCount() == 0)
        {
            progress_view.data()->close();
            m_ui.progress_view_checkbox->hide();
            showFinishInformation();
        }
    }

    available_packages_column.data()->clear();
    installed_packages_column.data()->clear();
    updated_packages_column.data()->clear();
    startAnimations();
    run();
}


void MainWindowView::checkUpdates()
{
   is_operation_running = true;
   Logger::logger()->logInfo(QStringLiteral("Start check updates - %1").arg(QDateTime::currentDateTime().toString()));

   updated_packages_column.data()->clear();
   m_ui.update_spinning_widget->show();
   spinning_animation->startOnWidget(m_ui.update_spinning_label);
   QThread* updated_packages_thread(new QThread);
   m_ui.packages_to_update_list->hide();
   m_ui.search_packages_to_update_checkbox->setEnabled(false);
   m_ui.check_all_updates_checkbox->setEnabled(false);
   QObject::connect(updated_packages_thread, &QThread::started, this, [this]() { updated_packages_column->fill(); emit packagesToUpdateFillEnded(); });
   QObject::connect(updated_packages_thread, &QThread::finished, updated_packages_thread, &QThread::deleteLater);

   QObject::connect(this, &MainWindowView::startOtherThreads, this, [updated_packages_thread]()
   {
       updated_packages_thread->start(QThread::TimeCriticalPriority);
   });
}


void MainWindowView::updateWidgets()
{
    Logger::logger()->logInfo("Update widgets and data after settings change");
    updatePreviewsDesign();
    startInternetCheckTimer();
    Logger::logger()->reopenFile();
}


void MainWindowView::checkRunningThreadsBeforeQuit()
{
    if (is_operation_running)
    {
        QMessageBox::warning(this, i18n("Quit"), i18n("Application cannot be closed immediately. Try again after end of running operations."));
        return;
    }

    QApplication::closeAllWindows();
}


void MainWindowView::refresh()
{
    is_operation_running = true;
    hideWidgets();
    emit initStarted();

    available_packages_column.data()->clear();
    installed_packages_column.data()->clear();
    updated_packages_column.data()->clear();

    startAnimations();
    run();
}


void MainWindowView::startAnimations()
{
    m_ui.remove_spinning_widget->show();
    m_ui.installation_spinning_widget->show();
    m_ui.update_spinning_widget->show();

    spinning_animation->startOnMainWidgets(m_ui.installation_spinning_label,
                                           m_ui.remove_spinning_label,
                                           m_ui.update_spinning_label);
}
