// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of CachyOS package manager based on "pak" application.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "mainwindowview.h"

#include "availablepackagescolumn.h"
#include "installedpackagescolumn.h"
#include "mainwindowviewsignals.h"
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
#include "settings.h"

#include <KLocalizedString>
#include <KLed>
#include <QCheckBox>
#include <QScopedPointer>
#include <QPushButton>
#include <QProcess>
#include <QPointer>
#include <QScopedPointer>
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
      main_window_view_signals(new MainWindowViewSignals(this)),
      process(nullptr),
      actions_access_checker(nullptr),
      internet_connection_timer(new QTimer(this)),
      current_state(State::Running)
{
    m_ui.setupUi(this);

    m_ui.input_update_widget->setHidden(true);
    m_ui.input_install_widget->setHidden(true);
    m_ui.input_uninstall_widget->setHidden(true);

    main_window_view_signals->attachInputAnswerLines();

    m_ui.aur_led_label->setToolTip(i18n("Internet connection state and auracle-git package presence"));
    m_ui.polaur_led_label->setToolTip(i18n("Internet connection state and git package presence"));
    m_ui.repo_led_label->setToolTip(i18n("Internet connection state"));
}


MainWindowView::~MainWindowView()
{
    available_packages_column->clearPackages();
    installed_packages_column->clearPackages();
    updated_packages_column->clearPackages();

    if (!internet_connection_timer.isNull())
    {
        internet_connection_timer->stop();
        delete internet_connection_timer;
    }
}


void MainWindowView::setProcess(const QSharedPointer<Process>& new_process)
{
    process = new_process;
}


void MainWindowView::setActionsAccessChecker(const QSharedPointer<ActionsAccessChecker>& new_actions_access_checker)
{
    actions_access_checker = new_actions_access_checker;
}


void MainWindowView::init()
{
    available_packages_column.reset(new AvailablePackagesColumn(m_ui.available_packages_list, m_ui.search_available_packages_lineedit, m_ui.sort_available_packages, this), &QObject::deleteLater);
    installed_packages_column.reset(new InstalledPackagesColumn(m_ui.installed_packages_list, m_ui.search_installed_packages_lineedit, m_ui.sort_installed_packages, this), &QObject::deleteLater);
    updated_packages_column.reset(new UpdatedPackagesColumn(m_ui.packages_to_update_list, m_ui.search_packages_to_update_lineedit, m_ui.sort_packages_to_update, this), &QObject::deleteLater);

    main_window_view_signals->initColumns();
    main_window_view_signals->initSignals();

    hideWidgets();

    main_window_view_signals->startInternetCheckTimer();
    main_window_view_signals->startPackagesCheckTimer();

    startAnimations();
}


void MainWindowView::run()
{
    checkUpdates();

    // ensuring update thread start before the next ones
    QObject::connect(&threads_timer, &QTimer::timeout, this, [this]()
        {
            m_ui.available_packages_list->hide();
            m_ui.installed_packages_list->hide();
            m_ui.search_available_packages_checkbox->setEnabled(false);
            m_ui.search_installed_packages_checkbox->setEnabled(false);

            main_window_view_signals->attachFillColumns();
            QObject::disconnect(&threads_timer, &QTimer::timeout, this, nullptr);
        });

    threads_timer.start(3000);
}


void MainWindowView::hideWidgets()
{
    m_ui.sort_installed_packages->setCheckState(Qt::Unchecked);
    m_ui.search_installed_packages_lineedit->clear();
    m_ui.search_installed_packages_checkbox->setCheckState(Qt::Unchecked);

    m_ui.console_view_uninstall->setCheckState(Qt::Unchecked);

    m_ui.installed_preview_area->hide();
    m_ui.progress_view_checkbox->hide();
    m_ui.sort_installed_packages->hide();
    m_ui.search_installed_packages_lineedit->hide();
    m_ui.installed_packages_list->hide();
    hideWidgetsExceptInstalled();
}


void MainWindowView::hideWidgetsExceptInstalled()
{
    m_ui.search_packages_to_update_lineedit->clear();
    m_ui.search_available_packages_lineedit->clear();
    m_ui.sort_available_packages->setCheckState(Qt::Unchecked);
    m_ui.sort_packages_to_update->setCheckState(Qt::Unchecked);
    m_ui.search_available_packages_checkbox->setCheckState(Qt::Unchecked);
    m_ui.console_view_install->setCheckState(Qt::Unchecked);

    m_ui.check_all_updates_checkbox->setCheckState(Qt::Unchecked);
    m_ui.search_packages_to_update_checkbox->setCheckState(Qt::Unchecked);
    m_ui.console_view_update->setCheckState(Qt::Unchecked);

    m_ui.updated_preview_area->hide();
    m_ui.available_preview_area->hide();
    m_ui.sort_available_packages->hide();
    m_ui.sort_packages_to_update->hide();
    m_ui.search_packages_to_update_lineedit->hide();
    m_ui.search_available_packages_lineedit->hide();
    m_ui.available_packages_list->hide();
    m_ui.packages_to_update_list->hide();
}


void MainWindowView::showFinishInformation()
{
    QMessageBox::information(this, i18n("All processes ended"), i18n("All processes have been completed."));
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

// TODOJG - to strategy design pattern
void MainWindowView::clearMainPreviews(Process::Task task)
{
    if ((Process::Task::UpdateAll == task) ||
        (Process::Task::Update == task))
    {
        //m_ui.text_browser_tab_update->clear();
        m_ui.input_for_update_lineedit->clear();
        m_ui.input_update_widget->setHidden(true);
    }

    if (Process::Task::Install == task)
    {
        //m_ui.text_browser_tab_install->clear();
        m_ui.input_for_install_lineedit->clear();
        m_ui.input_install_widget->setHidden(true);
    }

    if (Process::Task::Uninstall == task)
    {
        //m_ui.text_browser_tab_uninstall->clear();
        m_ui.input_for_uninstall_lineedit->clear();
        m_ui.input_uninstall_widget->setHidden(true);
    }
}


void MainWindowView::disconnectSortSignals()
{
    disconnect(m_ui.sort_installed_packages, &QCheckBox::toggled, installed_packages_column.data(), &InstalledPackagesColumn::sort);
    installed_packages_column->clearForSort();
    disconnect(m_ui.sort_packages_to_update, &QCheckBox::toggled, updated_packages_column.data(), &UpdatedPackagesColumn::sort);
    disconnect(m_ui.sort_available_packages, &QCheckBox::toggled, available_packages_column.data(), &AvailablePackagesColumn::sort);
    updated_packages_column->clearForSort();
    available_packages_column->clearForSort();
}


void MainWindowView::reconnectSortSignals()
{
    connect(m_ui.sort_installed_packages, &QCheckBox::toggled, installed_packages_column.data(), &InstalledPackagesColumn::sort);
    installed_packages_column->fillForSort();
    connect(m_ui.sort_packages_to_update, &QCheckBox::toggled, updated_packages_column.data(), &UpdatedPackagesColumn::sort);
    connect(m_ui.sort_available_packages, &QCheckBox::toggled, available_packages_column.data(), &AvailablePackagesColumn::sort);
    updated_packages_column->fillForSort();
    available_packages_column->fillForSort();
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
    {
        m_ui.packages_to_update_list->show();
        m_ui.search_packages_to_update_checkbox->setEnabled(true);
        m_ui.check_all_updates_checkbox->setEnabled(true);
        m_ui.update_packages_button->setEnabled(false);
        m_ui.sort_packages_to_update->setEnabled(true);
        m_ui.search_packages_to_update_lineedit->setEnabled(true);
    }

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
    if (m_ui.remove_spinning_widget->isHidden() &&
        m_ui.installation_spinning_widget->isHidden() &&
        actions_access_checker->isOnline())
    {
        emit initEnded();
        Logger::logger()->logInfo(QStringLiteral("Refresh/initialization ended"));

        if (!m_ui.update_spinning_widget->isHidden())
            return;

        current_state = State::Waiting;
        spinning_animation->stopOnMainWidgets(m_ui.installation_spinning_label,
                                              m_ui.remove_spinning_label,
                                              m_ui.update_spinning_label);

    }
}

// TODOJG - to strategy design pattern
void MainWindowView::showInputWidgets(Process::Task task)
{
    if ((Process::Task::UpdateAll == task) ||
        (Process::Task::Update == task))
    {
        m_ui.input_update_widget->setHidden(false);
    }

    if (Process::Task::Install == task)
    {
        m_ui.input_install_widget->setHidden(false);
    }

    if (Process::Task::Uninstall == task)
    {
        m_ui.input_uninstall_widget->setHidden(false);
    }
}

// TODOJG - to strategy design pattern
void MainWindowView::showSingleAnimation(Process::Task task)
{
    if ((Process::Task::UpdateAll == task) ||
        (Process::Task::Update == task))
    {
        m_ui.packages_to_update_label->setText(i18n("TO UPDATE"));
        m_ui.update_packages_button->setDisabled(true);
        m_ui.update_spinning_widget->show();
        m_ui.packages_to_update_list->hide();
        spinning_animation->startOnWidget<2>(m_ui.update_spinning_label);
    }

    if (Process::Task::Install == task)
    {
        m_ui.accessible_packages->setText(i18n("AVAILABLE TO INSTALL"));
        m_ui.install_packages_button->setDisabled(true);
        m_ui.installation_spinning_widget->show();
        m_ui.available_packages_list->hide();
        spinning_animation->startOnWidget<3>(m_ui.installation_spinning_label);
    }

    if (Process::Task::Uninstall == task)
    {
        m_ui.installed_packages_label->setText(i18n("INSTALLED"));
        m_ui.uninstall_packages_button->setDisabled(true);
        m_ui.remove_spinning_widget->show();
        m_ui.installed_packages_list->hide();
        spinning_animation->startOnWidget<1>(m_ui.remove_spinning_label);
    }
}


void MainWindowView::generatePreview(Process::Task task)
{
    QString task_text = QVariant::fromValue(task).toString().toLower();
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
    text_browser_tab->setObjectName(QString("text_browser_tab_%1").arg(task_text));
    vertical_layout2->addWidget(text_browser_tab);

    if (Settings::records()->operateOnActionsManually())
        addInputWidgets(vertical_layout2, scroll_area_widget_contents, task_text);

    scroll_area->setWidget(scroll_area_widget_contents);
    vertical_layout->addWidget(scroll_area);
    generated_previews_map.insert(task, operation_preview);
    progress_view.data()->addProgressView(operation_preview);

    if (Settings::records()->operateOnActionsManually())
        progress_view.data()->createSignals(task, process);

    emit operationsAmountIncreased();
}


void MainWindowView::addInputWidgets(QVBoxLayout*& vbox_layout,
                                     QWidget*& scroll_area_widget_contents,
                                     const QString& text)
{
    auto input_widget = new QWidget(scroll_area_widget_contents);
    input_widget->setObjectName(QString::fromUtf8("input_%1_widget").arg(text));
    auto horizontal_layout = new QHBoxLayout(input_widget);
    horizontal_layout->setObjectName(QString::fromUtf8("horizontal_layout_%1").arg(text));
    auto input_lineedit = new QLineEdit(input_widget);
    input_lineedit->setObjectName(QString::fromUtf8("input_for_%1_lineedit").arg(text));

    horizontal_layout->addWidget(input_lineedit);

    auto input_btn = new QPushButton(input_widget);
    input_btn->setText(i18n("Input"));
    input_btn->setObjectName(QString::fromUtf8("input_for_%1_btn").arg(text));
    input_btn->setMaximumSize(QSize(50, 16777215));

    horizontal_layout->addWidget(input_btn);

    vbox_layout->addWidget(input_widget);
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
    QPointer<DownloaderWindow> package_input(new PackageInput(download_command_parser));
    QPointer<DownloaderWindow> paths_choice_input(new PathsChoiceInput(download_command_parser));
    QPointer<DownloaderWindow> repos_choice_input(new ReposChoiceInput(download_command_parser));

    QObject::connect(qobject_cast<ReposChoiceInput*>(repos_choice_input.data()), &ReposChoiceInput::acceptedChoice, qobject_cast<PackageInput*>(package_input.data()), &PackageInput::closeWindow);

    QObject::connect(package_input, &DownloaderWindow::ended, package_input, &PackageInput::deleteLater);
    QObject::connect(package_input, &DownloaderWindow::ended, paths_choice_input, &PathsChoiceInput::deleteLater);
    QObject::connect(package_input, &DownloaderWindow::ended, repos_choice_input, &ReposChoiceInput::deleteLater);

    package_input->setNext(paths_choice_input)->setNext(repos_choice_input);
    package_input->handle();
}


void MainWindowView::searchPackage()
{
    QSharedPointer<InstallCommandParser> search_command_parser(new InstallCommandParser(), &QObject::deleteLater);
    QPointer<SearchWindow> package_input(new PackageSearchInput(search_command_parser));
    QPointer<SearchWindow> search_results_list(new SearchResultsList(search_command_parser, process, updated_packages_column->getCurrentPackagesCount()));

    QObject::connect(qobject_cast<SearchResultsList*>(search_results_list.data()), &SearchResultsList::acceptedChoice, qobject_cast<PackageSearchInput*>(package_input.data()), &PackageSearchInput::closeWindow);

    QObject::connect(package_input, &SearchWindow::ended, package_input, &PackageSearchInput::deleteLater);
    QObject::connect(package_input, &SearchWindow::ended, search_results_list, &PackageSearchInput::deleteLater);
    QObject::connect(search_results_list, &SearchWindow::ended, package_input, &PackageSearchInput::deleteLater);
    QObject::connect(search_results_list, &SearchWindow::ended, search_results_list, &PackageSearchInput::deleteLater);

    package_input->setNext(search_results_list);
    package_input->handle();
}

// TODOJG - to strategy design pattern
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
        auto foundTextBrowser = generated_previews_map.value(task)->findChild<QTextBrowser*>(QString("text_browser_tab_%1").arg(QVariant::fromValue(task).toString().toLower()));
        if (foundTextBrowser)
            foundTextBrowser->append(line);
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
    clearMainPreviews(task);
    Process::resetRunningTask(task);
    startAnimations();
    run();
}


void MainWindowView::checkUpdates()
{
    Logger::logger()->logInfo(QStringLiteral("Start check updates - %1").arg(QDateTime::currentDateTime().toString()));

    updated_packages_column.data()->clear();
    blockUpdateColumn();
    main_window_view_signals->attachCheckUpdates();
}


void MainWindowView::updateWidgets()
{
    Logger::logger()->logInfo("Update widgets and data after settings change");
    updatePreviewsDesign();
    main_window_view_signals->startInternetCheckTimer();
    Logger::logger()->reopenFile();
}


void MainWindowView::checkRunningThreadsBeforeQuit()
{
    if (current_state == State::Running)
    {
        QMessageBox::warning(this, i18n("Quit"), i18n("Application cannot be closed immediately. Try again after end of running operations."));
        return;
    }

    QApplication::closeAllWindows();
}


void MainWindowView::blockUpdateColumn()
{
    m_ui.update_spinning_widget->show();
    spinning_animation->startOnWidget<2>(m_ui.update_spinning_label);
    m_ui.packages_to_update_list->hide();
    m_ui.search_packages_to_update_checkbox->setCheckState(Qt::Unchecked);
    m_ui.search_packages_to_update_checkbox->setEnabled(false);
    m_ui.check_all_updates_checkbox->setCheckState(Qt::Unchecked);
    m_ui.check_all_updates_checkbox->setEnabled(false);
    m_ui.sort_packages_to_update->setCheckState(Qt::Unchecked);
    m_ui.sort_packages_to_update->hide();
    m_ui.search_packages_to_update_lineedit->clear();
    m_ui.search_packages_to_update_lineedit->hide();
    m_ui.update_packages_button->setEnabled(false);
    m_ui.sort_packages_to_update->setEnabled(false);
    m_ui.search_packages_to_update_lineedit->setEnabled(false);
}


void MainWindowView::refresh()
{
    if (current_state == State::Running)
    {
        Logger::logger()->logInfo(QStringLiteral("Waiting until all major processes are complete"));

        #ifdef RUN_TESTS
          return;
        #endif

        QMessageBox::information(this, i18n("Process running"), i18n("Wait until all major processes are complete"));
        return;
    }

    current_state = State::Running;
    disconnectSortSignals();
    hideWidgets();
    emit initStarted();

    available_packages_column.data()->clear();
    installed_packages_column.data()->clear();
    updated_packages_column.data()->clear();

    startAnimations();
    run();
    reconnectSortSignals();
}


void MainWindowView::startAnimations()
{
    m_ui.packages_to_update_label->setText(i18n("TO UPDATE"));
    m_ui.accessible_packages->setText(i18n("AVAILABLE TO INSTALL"));
    m_ui.installed_packages_label->setText(i18n("INSTALLED"));

    m_ui.remove_spinning_widget->show();
    m_ui.installation_spinning_widget->show();
    m_ui.update_spinning_widget->show();

    spinning_animation->startOnMainWidgets(m_ui.installation_spinning_label,
                                           m_ui.remove_spinning_label,
                                           m_ui.update_spinning_label);
}
