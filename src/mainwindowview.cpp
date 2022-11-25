#include "mainwindowview.h"

#include "availablepackagescolumn.h"
#include "installedpackagescolumn.h"
#include "updatedpackagescolumn.h"
#include "pakGuiSettings.h"
#include "statistics.h"
#include "statisticscommandparser.h"
#include "process.h"
#include "packagedownloader.h"
#include "previewdesign.h"
#include "logger.h"
#include "defs.h"

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
#include <QtConcurrent/QtConcurrent>


MainWindowView::MainWindowView(QSharedPointer<Process> new_process,
                               QSharedPointer<ActionsAccessChecker> new_actions_access_checker,
                               QWidget *parent)
    : QWidget(parent),
      process(new_process),
      actions_access_checker(new_actions_access_checker),
      generated_previews_map(QMap<Process::Task, QPointer<QWidget>>()),
      progress_view(QSharedPointer<ProgressView>(new ProgressView)),
      spinning_animation(nullptr)

{
    m_ui.setupUi(this);

    PreviewDesign::update(m_ui.text_browser_tab_uninstall);
    PreviewDesign::update(m_ui.text_browser_tab_install);
    PreviewDesign::update(m_ui.text_browser_tab_update);

    available_packages_column = QSharedPointer<AvailablePackagesColumn>(new AvailablePackagesColumn(m_ui.available_packages_list, m_ui.search_available_packages_lineedit), &QObject::deleteLater);
    installed_packages_column = QSharedPointer<InstalledPackagesColumn>(new InstalledPackagesColumn(m_ui.installed_packages_list, m_ui.search_installed_packages_lineedit), &QObject::deleteLater);
    updated_packages_column = QSharedPointer<UpdatedPackagesColumn>(new UpdatedPackagesColumn(m_ui.packages_to_update_list, m_ui.search_packages_to_update_lineedit), &QObject::deleteLater);

    emit initStarted();
    Logger::logger()->logInfo("Initialization started");

    generated_previews_map.insert(Process::Task::Install, m_ui.installed_preview_area);
    generated_previews_map.insert(Process::Task::Uninstall, m_ui.updated_preview_area);
    generated_previews_map.insert(Process::Task::Update, m_ui.available_preview_area);

    QObject::connect(actions_access_checker.get(), &ActionsAccessChecker::internetAccessChanged, this, &MainWindowView::toggleWidgetsAccess);
    QObject::connect(actions_access_checker.get(), &ActionsAccessChecker::auracleAccessChanged, [this](bool is_auracle_installed){ is_auracle_installed && actions_access_checker->isOnline() ? m_ui.aur_kled->on() : m_ui.aur_kled->off();});
    QObject::connect(actions_access_checker.get(), &ActionsAccessChecker::gitAccessChanged, [this](bool is_git_installed){ is_git_installed && actions_access_checker->isOnline() ? m_ui.polaur_kled->on() : m_ui.polaur_kled->off();});
    QObject::connect(this, &MainWindowView::operationsAmountIncreased, m_ui.progress_view_checkbox, &QCheckBox::show);
    QObject::connect(progress_view.data(), &QDialog::rejected, [this](){ m_ui.progress_view_checkbox->setChecked(false); });
    QObject::connect(m_ui.progress_view_checkbox, &QCheckBox::toggled, [=](bool is_checked) { if (is_checked) progress_view.data()->show(); else progress_view.data()->hide(); });
    QObject::connect(m_ui.console_view_install, &QCheckBox::toggled, [=](bool is_checked) { if (is_checked) m_ui.available_preview_area->show(); else m_ui.available_preview_area->hide(); });
    QObject::connect(m_ui.console_view_uninstall, &QCheckBox::toggled, [=](bool is_checked) { if (is_checked) m_ui.installed_preview_area->show(); else m_ui.installed_preview_area->hide(); });
    QObject::connect(m_ui.console_view_update, &QCheckBox::toggled, [=](bool is_checked) { if (is_checked) m_ui.updated_preview_area->show(); else m_ui.updated_preview_area->hide(); });

    QObject::connect(process.data(), &Process::generatedOutput, this, &MainWindowView::generateOutput, Qt::AutoConnection);
    QObject::connect(process.data(), &Process::acceptedTask, this, &MainWindowView::generatePreview);
    QObject::connect(process.data(), &Process::acceptedTask, this, &MainWindowView::showAnimation);
    QObject::connect(process.data(), &Process::finished, this, [=](Process::Task task, int exit_code, QProcess::ExitStatus exit_status) { finishProcess(task, exit_code, exit_status); }, Qt::AutoConnection);
    QObject::connect(process.data(), &Process::finished, this, &MainWindowView::stopAnimation);

    hideWidgets();
    setTimerOnActionsAccessChecker();
    startAnimations();
    init();
}


MainWindowView::~MainWindowView()
{

}


void MainWindowView::init()
{
    QThread* available_packages_thread(new QThread);
    QThread* installed_packages_thread(new QThread);
    QThread* updated_packages_thread(new QThread);

    m_ui.available_packages_list->hide();
    m_ui.installed_packages_list->hide();
    m_ui.packages_to_update_list->hide();

    QObject::connect(updated_packages_thread, &QThread::started, [this]() { updated_packages_column->fill(); emit packagesToUpdateFillEnded(); });
    QObject::connect(available_packages_thread, &QThread::started, [this]() {  available_packages_column->fill(); emit availablePackagesFillEnded(); });
    QObject::connect(installed_packages_thread, &QThread::started, [this]() { installed_packages_column->fill(); emit installedPackagesFillEnded(); });
    QObject::connect(updated_packages_column.get(), &UpdatedPackagesColumn::startOtherThreads, [this]()
    {
        emit startOtherThreads();
    });
    QObject::connect(this, &MainWindowView::startOtherThreads, [=]()
    {
        available_packages_thread->start();
        installed_packages_thread->start();
    });
    QObject::connect(this, &MainWindowView::availablePackagesFillEnded, this, &MainWindowView::connectSignalsForAvailablePackages);
    QObject::connect(this, &MainWindowView::installedPackagesFillEnded, this, &MainWindowView::connectSignalsForInstalledPackages);
    QObject::connect(this, &MainWindowView::packagesToUpdateFillEnded, this, &MainWindowView::connectSignalsForUpdatedPackages);
    QObject::connect(available_packages_thread, &QThread::finished, available_packages_thread, &QThread::deleteLater);
    QObject::connect(installed_packages_thread, &QThread::finished, installed_packages_thread,  &QThread::deleteLater);
    QObject::connect(updated_packages_thread, &QThread::finished, updated_packages_thread, &QThread::deleteLater);

    updated_packages_thread->start(QThread::InheritPriority);
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


void MainWindowView::setTimerOnActionsAccessChecker()
{
    QPointer<QTimer> internet_connection_timer = new QTimer(this);
    QPointer<QTimer> packages_timer = new QTimer(this);
    connect(internet_connection_timer, &QTimer::timeout, actions_access_checker.get(), &ActionsAccessChecker::checkInternetConnection);
    connect(packages_timer, &QTimer::timeout, actions_access_checker.get(), &ActionsAccessChecker::checkRequiredPackages);
    int miliseconds = Converter::minutesToMiliseconds(pakGuiSettings::internet_reconnection_time_in_minutes());
    startCheckTimer(internet_connection_timer, miliseconds, QString("Internet connection checker "));
    startCheckTimer(packages_timer, 8000, QString("Required packages checker "));
}


void MainWindowView::startCheckTimer(QPointer<QTimer> timer, int miliseconds, const QString& timer_type)
{
    timer->start(miliseconds);

    if (miliseconds == 0)
        timer->stop();

    Logger::logger()->logDebug(QStringLiteral("%1 started with interval %2").arg(timer_type).arg(miliseconds));
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
    {
        m_ui.available_packages_list->show();
        m_ui.search_available_packages_checkbox->setEnabled(true);
    }

    m_ui.installation_spinning_widget->hide();
    QObject::connect(m_ui.sort_available_packages, &QCheckBox::toggled, available_packages_column.data(), &AvailablePackagesColumn::sort, Qt::AutoConnection);
    QObject::connect(m_ui.available_packages_list, &QListWidget::itemChanged, available_packages_column.data(), &AvailablePackagesColumn::updateCheckedPackagesCounter, Qt::AutoConnection);
    QObject::connect(available_packages_column.data(), &AvailablePackagesColumn::checkedPackagesCounterChanged, this, [this](bool has_checked_buttons) { m_ui.install_packages_button->setEnabled(has_checked_buttons); });
    QObject::connect(m_ui.install_packages_button, &QPushButton::clicked, this, [this]() { m_ui.text_browser_tab_install->clear(); process->run(Process::Task::Install, available_packages_column.data()->collectCheckedPackages()); }, Qt::AutoConnection);
    checkSpinningVisibility();
}


void MainWindowView::connectSignalsForInstalledPackages()
{
    if (m_ui.installed_packages_list->count() > 0)
    {
        m_ui.installed_packages_list->show();
        m_ui.search_installed_packages_checkbox->setEnabled(true);
    }

    m_ui.remove_spinning_widget->hide();
    QObject::connect(m_ui.sort_installed_packages, &QCheckBox::toggled, installed_packages_column.data(), &InstalledPackagesColumn::sort, Qt::AutoConnection);
    QObject::connect(m_ui.installed_packages_list, &QListWidget::itemChanged, installed_packages_column.data(), &InstalledPackagesColumn::updateCheckedPackagesCounter, Qt::AutoConnection);
    QObject::connect(installed_packages_column.data(), &InstalledPackagesColumn::checkedPackagesCounterChanged, this, [this](bool has_checked_buttons) { m_ui.uninstall_packages_button->setEnabled(has_checked_buttons); }, Qt::AutoConnection);
    QObject::connect(m_ui.uninstall_packages_button, &QPushButton::clicked, this, [this]() { m_ui.text_browser_tab_uninstall->clear(); process->run(Process::Task::Uninstall, installed_packages_column.data()->collectCheckedPackages()); }, Qt::AutoConnection);
    checkSpinningVisibility();
}


void MainWindowView::connectSignalsForUpdatedPackages()
{
    if (m_ui.packages_to_update_list->count() > 0)
    {
        m_ui.packages_to_update_list->show();
        m_ui.search_packages_to_update_checkbox->setEnabled(true);
    }

    if (m_ui.packages_to_update_list->count() == 0 && actions_access_checker->isOnline())
    {
        m_ui.packages_to_update_label->setStyleSheet("color: black; font-size: 15px;");
        m_ui.packages_to_update_label->setText(i18n("There aren't packages to update"));
    }

    m_ui.update_spinning_widget->hide();
    QObject::connect(m_ui.sort_packages_to_update, &QCheckBox::toggled, updated_packages_column.data(), &UpdatedPackagesColumn::sort, Qt::AutoConnection);
    QObject::connect(m_ui.packages_to_update_list, &QListWidget::itemChanged, updated_packages_column.data(), &UpdatedPackagesColumn::updateCheckedPackagesCounter, Qt::AutoConnection);
    QObject::connect(updated_packages_column.data(), &UpdatedPackagesColumn::checkedPackagesCounterChanged, this, [this](bool has_checked_buttons) { m_ui.update_packages_button->setEnabled(has_checked_buttons); }, Qt::AutoConnection);
    QObject::connect(m_ui.update_packages_button, &QPushButton::clicked, this, [this]() { m_ui.text_browser_tab_update->clear(); process->run(Process::Task::Update, updated_packages_column.data()->collectCheckedPackages()); }, Qt::AutoConnection);
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
        spinning_animation->stop();
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


void MainWindowView::showAnimation()
{
    spinning_animation.reset(new QMovie(":/waiting-small.gif"), &QObject::deleteLater);
    m_ui.actions_spinning_animation_label->setMovie(spinning_animation.get());
    m_ui.actions_spinning_animation_label->show();
    spinning_animation->start();
    Logger::logger()->logDebug(QStringLiteral("Animation in main window started"));
}


void MainWindowView::stopAnimation()
{
    m_ui.actions_spinning_animation_label->hide();
    spinning_animation->stop();
    Logger::logger()->logDebug(QStringLiteral("Animation in main window stopped"));
}


void MainWindowView::showStatisticsWindow()
{
    QScopedPointer<StatisticsCommandParser> command_parser(new StatisticsCommandParser);
    auto list_result = command_parser.data()->retrieveInfo();
    auto map_result = command_parser.data()->convertToMap(list_result);

    QPointer<Statistics> statistics = new Statistics(map_result, this);
    statistics->resize(800, 500);
    statistics->show();
}


void MainWindowView::downloadPackage()
{
    QPointer<DownloadCommandParser> download_command_parser(new DownloadCommandParser(QString()));
    QPointer<DownloaderWindow> automatic_installation(new AutomaticInstallation(download_command_parser));
    QPointer<DownloaderWindow> package_input(new PackageInput(download_command_parser));
    QPointer<DownloaderWindow> paths_choice_input(new PathsChoiceInput(download_command_parser));
    QPointer<DownloaderWindow> repos_choice_input(new ReposChoiceInput(download_command_parser));

    automatic_installation->setNext(package_input)->setNext(paths_choice_input)->setNext(repos_choice_input);
    automatic_installation->handle();
}


void MainWindowView::generateOutput(Process::Task task, const QString& line)
{
    switch(task)
    {
    case Process::Task::Install:
        m_ui.text_browser_tab_install->append(line);
        break;

    case Process::Task::Update:
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
    if (task != Process::Task::Install &&
        task != Process::Task::Update &&
        task != Process::Task::Uninstall)
    {
        progress_view.data()->removeProgressView(generated_previews_map.value(task));
        generated_previews_map.remove(task);
        if (progress_view.data()->tabsCount() == 0)
        {
            progress_view.data()->close();
            m_ui.progress_view_checkbox->hide();
            QMessageBox::information(this, i18n("All processes ended"), i18n("All processes have been completed."));
        }
    }

    available_packages_column.data()->clear();
    installed_packages_column.data()->clear();
    updated_packages_column.data()->clear();
    startAnimations();
    init();
}


void MainWindowView::refresh()
{
    hideWidgets();
    emit initStarted();

    available_packages_column.data()->clear();
    installed_packages_column.data()->clear();
    available_packages_column.data()->clear();

    startAnimations();
    init();
}


void MainWindowView::startAnimations()
{
    m_ui.remove_spinning_widget->show();
    m_ui.installation_spinning_widget->show();
    m_ui.update_spinning_widget->show();

    spinning_animation.reset(new QMovie(":/waiting.gif"), &QObject::deleteLater);
    m_ui.installation_spinning_label->setMovie(spinning_animation.get());
    m_ui.remove_spinning_label->setMovie(spinning_animation.get());
    m_ui.update_spinning_label->setMovie(spinning_animation.get());
    spinning_animation->start();
}

