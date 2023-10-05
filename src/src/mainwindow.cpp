// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of package manager based on "pak" application.
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

#include "mainwindow.h"

#include "actionsaccesschecker.h"
#include "kstandardaction.h"
#include "kxmlguiwindow.h"
#include "mainwindowview.h"
#include "settingsrecords.h"
#include "src/settings.h"
#include "src/systemtray.h"
#include "timeconverter.h"
#include "logger.h"

#include <QAction>
#include <QStatusBar>
#include <QMenu>
#include <QMenuBar>
#include <QDomDocument>

#include <KActionCollection>
#include <KConfigDialog>
#include <KLocalizedString>
#include <KStandardAction>
#include <KNotification>
#include <KHelpMenu>
#include <KXMLGUIFactory>


MainWindow::MainWindow()
  : KXmlGuiWindow(),
    actions_access_checker{ActionsAccessChecker::actionsAccessChecker(this)},
    settings_window{nullptr},
    help_menu{new KHelpMenu(this, i18n("Other"), false)}
{
   setWindowState(windowState() ^ Qt::WindowMaximized);
   setHelpMenuEnabled(false);
   setStandardToolBarMenuEnabled(false);
}


MainWindow::~MainWindow()
{
    timer_on_logs.stop();
    timer_on_updates.stop();

    delete close_action;
    delete update_action;
    delete refresh_action;
    delete download_action;
    delete search_action;
    delete print_statistics_action;
    delete update_all_action;
    delete update_mirrors_action;
    delete clean_action;
    delete sync_polaur_action;
    delete switch_language;
    delete configure_shortcuts;
    delete configure_toolbar;
    delete configure_pak;
    delete help_menu;

    actions_access_checker.reset(nullptr);
    Settings::clearRecords();
    Logger::logger()->closeOnQuit();
}


void MainWindow::run()
{
    prepareProcess(QSharedPointer<Process>(new Process(actions_access_checker, this)));
    prepareMainWindowView(new MainWindowView(this));
    setCentralWidget(main_window_view);
    startSystemTray();
    initSignals();
    setupGUI(Save | Create, "pak-gui.rc");
    setXMLFile("pak-gui.rc", true);
}


void MainWindow::disableActions()
{
    update_action->setDisabled(true);
    refresh_action->setDisabled(true);
    download_action->setDisabled(true);
    update_all_action->setDisabled(true);
    update_mirrors_action->setDisabled(true);
    clean_action->setDisabled(true);
    print_statistics_action->setDisabled(true);
    search_action->setDisabled(true);
    sync_polaur_action->setDisabled(true);
}


void MainWindow::disableOnlineActions()
{
    update_action->setDisabled(true);
    download_action->setDisabled(true);
    update_all_action->setDisabled(true);
    update_mirrors_action->setDisabled(true);
    refresh_action->setDisabled(false);
    clean_action->setDisabled(false);
    print_statistics_action->setDisabled(false);
    search_action->setDisabled(true);
    sync_polaur_action->setDisabled(true);
}


void MainWindow::showAboutApp()
{
    Q_ASSERT(help_menu);
    help_menu->aboutApplication();
}


void MainWindow::reportBug()
{
    Q_ASSERT(help_menu);
    help_menu->reportBug();
}


void MainWindow::prepareMainWindowView(MainWindowView* main_window_view)
{
    this->main_window_view = main_window_view;
    main_window_view->setProcess(process.toWeakRef());
    main_window_view->setActionsAccessChecker(actions_access_checker.toWeakRef());
    main_window_view->init();
    main_window_view->preparePreviews();
    main_window_view->run();
}


void MainWindow::prepareProcess(const QWeakPointer<Process>& new_process)
{
    process = new_process.toStrongRef();
}


void MainWindow::setTimersOnChecks()
{
    if (!main_window_view.isNull())
        QObject::disconnect(&timer_on_updates, &QTimer::timeout, main_window_view, &MainWindowView::checkUpdates);

    QObject::disconnect(&timer_on_logs, &QTimer::timeout, Logger::logger(), &Logger::clearLogsFile);
    connectSignalForUpdateCheck();
    connectSignalForHistoryStore();
}


void MainWindow::startSystemTray()
{
    if (!main_window_view.isNull() && !system_tray_icon.isNull())
    {
        disconnect(main_window_view, &MainWindowView::initStarted, system_tray_icon.get(), &SystemTray::changeStatusToDefault);
        disconnect(main_window_view, &MainWindowView::packagesToUpdateCountChanged, system_tray_icon.get(), &SystemTray::update);
    }

    system_tray_icon.reset(nullptr);

    if (Settings::records()->useSystemTray())
    {
        system_tray_icon.reset(new SystemTray(this));
        system_tray_icon->addAction(i18n("Refresh"), refresh_action);
        connect(main_window_view, &MainWindowView::initStarted, system_tray_icon.get(), &SystemTray::changeStatusToDefault);
        connect(main_window_view, &MainWindowView::packagesToUpdateCountChanged, system_tray_icon.get(), &SystemTray::update);
    }
}


void MainWindow::startTimerOnOperation(const QDateTime& time,
                                       QTimer& timer,
                                       int time_limit_in_milliseconds,
                                       const QString& operation)
{
    if (!time.isValid() || time_limit_in_milliseconds == 0)
        return;

    qint64 time_passed_in_milliseconds = time.msecsTo(QDateTime::currentDateTime());
    qint64 rest_time = time_limit_in_milliseconds - time_passed_in_milliseconds;

    if (time_passed_in_milliseconds > time_limit_in_milliseconds)
    {
        Logger::logger()->logDebug(QStringLiteral("Restart timer for %1").arg(operation));
        Settings::saveInitDateTime(operation);
        rest_time = time_limit_in_milliseconds;
    }

    timer.start(rest_time);
    Logger::logger()->logDebug(QStringLiteral("Time passed for %1: %2")
                                   .arg(operation, TimeConverter::timeToString(time_passed_in_milliseconds)));
}


void MainWindow::setAction(QPointer<QAction>& action,
                           const MenuAction& menu_action_info)
{
    action = new QAction(this);
    action->setText(menu_action_info.text);
    action->setIcon(QIcon(":/icons/menu/" + menu_action_info.icon + ".png"));
    this->actionCollection()->setDefaultShortcut(action, menu_action_info.key_sequence);
    this->actionCollection()->addAction(menu_action_info.config_name, action);
}


void MainWindow::connectSignalForUpdateCheck()
{
    if (Settings::records()->updateCheckTimeDays() > 0 || Settings::records()->updateCheckTimeHours() > 0 ||
        Settings::records()->updateCheckTimeMinutes())
    {
        QObject::connect(&timer_on_updates, &QTimer::timeout, main_window_view, &MainWindowView::checkUpdates);
        startTimerOnOperation(Settings::records()->startDateTimeForUpdatesCheck(),
            timer_on_updates,
            TimeConverter::toMilliseconds(Settings::records()->updateCheckTimeDays(),
                Settings::records()->updateCheckTimeHours(),
                Settings::records()->updateCheckTimeMinutes()),
            QString("update"));
    }
}


void MainWindow::connectSignalForHistoryStore()
{
    if (Settings::records()->historyStoreTimeDays() > 0)
    {
        QObject::connect(&timer_on_logs, &QTimer::timeout, Logger::logger(), &Logger::clearLogsFile);
        startTimerOnOperation(Settings::records()->startDateTimeForHistoryStore(),
            timer_on_logs,
            TimeConverter::daysToMilliseconds(Settings::records()->historyStoreTimeDays()),
            QString("logs remove"));
    }
}


void MainWindow::initSignals()
{
    QObject::connect(actions_access_checker.get(), &ActionsAccessChecker::requiredPackagesNotFound, [this]() { emit closeApp(); });
    Settings::saveInitDateTimesWhenEmpty();
    setTimersOnChecks();

    KActionCollection* actionCollection = this->actionCollection();
    setAction(close_action, MenuAction{i18n("&Close"), QString("exit"), QString("close"), QKeySequence(Qt::CTRL, Qt::Key_Q)});
    connect(close_action, &QAction::triggered, main_window_view, &MainWindowView::checkRunningThreadsBeforeQuit);

    setAction(update_action, MenuAction{i18n("&Update"), QString("update"), QString("update"), QKeySequence(Qt::CTRL, Qt::Key_U)});
    connect(update_action, &QAction::triggered, this, [this]() { process->setAurPackagesToUpdate(main_window_view->getUpdatedPackagesColumn()->getNotRepoPackagesCount()); if (process->preparedBeforeRun(Process::Task::UpdateInstalledPackages)) process->run(Process::Task::UpdateInstalledPackages); }, Qt::AutoConnection);

    setAction(refresh_action, MenuAction{i18n("&Refresh"), QString("refresh"), QString("refresh"), QKeySequence(Qt::CTRL, Qt::Key_R)});
    connect(refresh_action, &QAction::triggered, main_window_view, &MainWindowView::refresh);

    connect(main_window_view, &MainWindowView::initStarted, this, &MainWindow::disableActions);
    connect(main_window_view, &MainWindowView::initEnded, this, &MainWindow::enableActions);
    connect(main_window_view, &MainWindowView::initStarted, this, [this](){ initEnded = false; });
    connect(main_window_view, &MainWindowView::initEnded, this, [this](){ initEnded = true; });
    connect(main_window_view, &MainWindowView::hideOnlineActions, this, &MainWindow::disableOnlineActions);
    connect(this, &MainWindow::updatedPackageInfoList, main_window_view, &MainWindowView::setForcedUpdateFlag);
    connect(this, &MainWindow::updatedPackageInfoList, main_window_view, &MainWindowView::refresh);
    connect(actions_access_checker.get(), &ActionsAccessChecker::reflectorAccessChanged, [this](bool is_installed) {
        update_mirrors_action->setEnabled(initEnded && is_installed); });

    connect(actions_access_checker.get(), &ActionsAccessChecker::gitAccessChanged, [this](bool is_installed) {
        sync_polaur_action->setEnabled(initEnded && is_installed); });

    setAction(download_action, MenuAction{i18n("&Download"), QString("download"), QString("download"), QKeySequence(Qt::CTRL, Qt::Key_D)});
    connect(download_action, &QAction::triggered, main_window_view, &MainWindowView::downloadPackage);

    setAction(search_action, MenuAction{i18n("&Search"), QString("search"), QString("search"), QKeySequence(Qt::CTRL, Qt::Key_S)});
    connect(search_action, &QAction::triggered, main_window_view, &MainWindowView::searchPackage);

    setAction(update_all_action, MenuAction{i18n("&Update system packages"), QString("update"), QString("updateAllPackages"), QKeySequence(Qt::CTRL, Qt::Key_U, Qt::Key_A)});
    connect(update_all_action, &QAction::triggered, this, [this]() { process->setAurPackagesToUpdate(main_window_view->getUpdatedPackagesColumn()->getNotRepoPackagesCount()); if (process->preparedBeforeRun(Process::Task::UpdateAll)) process->run(Process::Task::UpdateAll); }, Qt::AutoConnection);

    setAction(update_mirrors_action, MenuAction{i18n("&Update mirrors"), QString("update-mirrors"), QString("updateMirrors"), QKeySequence(Qt::CTRL, Qt::Key_U, Qt::Key_M)});
    connect(update_mirrors_action, &QAction::triggered, this, [this]() { if (process->preparedBeforeRun(Process::Task::MirrorsUpdate)) process->run(Process::Task::MirrorsUpdate); }, Qt::AutoConnection);

    setAction(clean_action, MenuAction{i18n("&Clean"), QString("clean"), QString("clean"), QKeySequence(Qt::CTRL, Qt::Key_C)});
    connect(clean_action, &QAction::triggered, this, [this]() { if (process->preparedBeforeRun(Process::Task::Clean)) process->run(Process::Task::Clean); }, Qt::AutoConnection);

    setAction(sync_polaur_action, MenuAction{i18n("&Sync POLAUR"), QString("synchronization"), QString("syncPOLAUR"), QKeySequence(Qt::CTRL, Qt::Key_S, Qt::Key_P)});
    connect(sync_polaur_action, &QAction::triggered, this, [this]() { if (process->preparedBeforeRun(Process::Task::SyncPOLAUR)) process->run(Process::Task::SyncPOLAUR); }, Qt::AutoConnection);

    setAction(print_statistics_action, MenuAction{i18n("&Statistics"), QString("statistics"), QString("statistics"), QKeySequence(Qt::CTRL, Qt::Key_S, Qt::Key_T)});
    connect(print_statistics_action, &QAction::triggered, main_window_view, &MainWindowView::showStatisticsWindow);

    setAction(switch_language, MenuAction{i18n("&Configure languages"), QString("configure-languages"), QString("configureLanguage"), QKeySequence(Qt::CTRL, Qt::Key_C, Qt::Key_L)});
    connect(switch_language, &QAction::triggered, help_menu, &KHelpMenu::switchApplicationLanguage);

    setAction(configure_shortcuts, MenuAction{i18n("&Configure shortcuts"), QString("configure-shortcuts"), QString("configureKeyboardShortcuts"), QKeySequence(Qt::CTRL, Qt::Key_S, Qt::Key_H)});
    connect(configure_shortcuts, &QAction::triggered, guiFactory(), &KXMLGUIFactory::showConfigureShortcutsDialog);

    setAction(configure_toolbar, MenuAction{i18n("&Configure toolbar"), QString("configure-toolbar"), QString("configureToolbars"), QKeySequence(Qt::CTRL, Qt::Key_C, Qt::Key_T)});
    connect(configure_toolbar, &QAction::triggered, this, &KXmlGuiWindow::configureToolbars);

    setAction(configure_pak, MenuAction{i18n("&Configure pak-gui"), QString("settings"), QString("configurePakGui"), QKeySequence(Qt::CTRL, Qt::Key_P, Qt::Key_G)});
    connect(configure_pak, &QAction::triggered, this, &MainWindow::settingsConfigure);

    auto handbook = KStandardAction::helpContents(this, &KXmlGuiWindow::appHelpActivated, actionCollection);
    handbook->setIcon(QIcon(":/icons/menu/handbook.png"));

    auto report_bug = KStandardAction::reportBug(this, &MainWindow::reportBug, actionCollection);
    report_bug->setIcon(QIcon(":/icons/menu/report-bug.png"));

    auto about_app = KStandardAction::aboutApp(this, &MainWindow::showAboutApp, actionCollection);
    about_app->setIcon(QIcon(":/icons/menu/pak-gui.png"));

    disableActions();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (Settings::records()->useSystemTray())
    {
        event->ignore();
        this->hide();
        return;
    }

    if (!main_window_view->isRunningMainThreads())
    {
        event->accept();
        return;
    }

    event->ignore();
}


void MainWindow::enableActions()
{
    update_action->setDisabled(false);
    refresh_action->setDisabled(false);
    download_action->setDisabled(false);
    update_all_action->setDisabled(false);
    clean_action->setDisabled(false);
    print_statistics_action->setDisabled(false);
    search_action->setDisabled(false);
}


void MainWindow::settingsConfigure()
{
    settings_window = new Settings(this);
    connect(settings_window, &Settings::settingsChanged, main_window_view, &MainWindowView::updateWidgets);
    settings_window->show();
    settings_window->raise();
}


void MainWindow::detachSettingsSignal()
{
    disconnect(settings_window, &Settings::settingsChanged, main_window_view, nullptr);
}
