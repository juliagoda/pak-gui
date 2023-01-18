#include "mainwindow.h"

#include "actionsaccesschecker.h"
#include "mainwindowview.h"
#include "settingsrecords.h"
#include "timeconverter.h"
#include "settings.h"
#include "logger.h"

#include <QAction>
#include <QStatusBar>

#include <KActionCollection>
#include <KConfigDialog>
#include <KLocalizedString>
#include <KStandardAction>
#include <KNotification>


MainWindow::MainWindow()
    : KXmlGuiWindow(),
      actions_access_checker(ActionsAccessChecker::actionsAccessChecker(this)),
      process(QSharedPointer<Process>(new Process(actions_access_checker, this))),
      system_tray_icon(nullptr)
{
    main_window_view = new MainWindowView(this);
    main_window_view->setProcess(process);
    main_window_view->setActionsAccessChecker(actions_access_checker);
    main_window_view->preparePreviews();
    main_window_view->run();
    setCentralWidget(main_window_view);
    startSystemTray();

    QObject::connect(actions_access_checker.get(), &ActionsAccessChecker::requiredPackagesNotFound, [this]() { emit closeApp(); });
    Settings::saveInitDateTimesWhenEmpty();
    setTimersOnChecks();

    KActionCollection* actionCollection = this->actionCollection();
    setAction(update_action, i18n("&Update"), QString("update"), QKeySequence(Qt::CTRL, Qt::Key_U));
    connect(update_action, &QAction::triggered, this, [this]() { process->run(Process::Task::UpdateInstalledPackages); }, Qt::AutoConnection);

    setAction(refresh_action, i18n("&Refresh"), QString("refresh"), QKeySequence(Qt::CTRL, Qt::Key_R));
    connect(refresh_action, &QAction::triggered, main_window_view, &MainWindowView::refresh);
    connect(main_window_view, &MainWindowView::initStarted, this, &MainWindow::disableActions);
    connect(main_window_view, &MainWindowView::initEnded, this, &MainWindow::enableActions);
    connect(main_window_view, &MainWindowView::hideOnlineActions, this, &MainWindow::disableOnlineActions);
    connect(this, &MainWindow::widgetsChanged, main_window_view, &MainWindowView::updateWidgets);
    connect(this, &MainWindow::updatedPackageInfoList, main_window_view, &MainWindowView::refresh);
    connect(actions_access_checker.get(), &ActionsAccessChecker::reflectorAccessChanged, [this](bool is_installed) {
        update_mirrors_action->setEnabled(is_installed); });

    setAction(download_action, i18n("&Download"), QString("download"), QKeySequence(Qt::CTRL, Qt::Key_D));
    connect(download_action, &QAction::triggered, main_window_view, &MainWindowView::downloadPackage);

    setAction(search_action, i18n("&Search"), QString("search"), QKeySequence(Qt::CTRL, Qt::Key_S));
    connect(search_action, &QAction::triggered, main_window_view, &MainWindowView::searchPackage);

    setAction(update_all_action, i18n("&Update all packages"), QString("updateAllPackages"), QKeySequence(Qt::CTRL, Qt::Key_U, Qt::Key_A));
    connect(update_all_action, &QAction::triggered, this, [this]() { process->run(Process::Task::UpdateAll); }, Qt::AutoConnection);

    setAction(update_mirrors_action, i18n("&Update mirrors"), QString("updateMirrors"), QKeySequence(Qt::CTRL, Qt::Key_U, Qt::Key_M));
    connect(update_mirrors_action, &QAction::triggered, this, [this]() { process->run(Process::Task::MirrorsUpdate); }, Qt::AutoConnection);

    setAction(clean_action, i18n("&Clean"), QString("clean"), QKeySequence(Qt::CTRL, Qt::Key_C));
    connect(clean_action, &QAction::triggered, this, [this]() { process->run(Process::Task::Clean); }, Qt::AutoConnection);

    setAction(print_statistics_action, i18n("&Statistics"), QString("statistics"), QKeySequence(Qt::CTRL, Qt::Key_S, Qt::Key_T));
    connect(print_statistics_action, &QAction::triggered, main_window_view, &MainWindowView::showStatisticsWindow);

    disableActions();

    KStandardAction::quit(main_window_view, SLOT(checkRunningThreadsBeforeQuit()), actionCollection);
    KStandardAction::preferences(this, SLOT(settingsConfigure()), actionCollection);

    setupGUI(Default, "pak-gui.rc");
    setXMLFile("pak-gui.rc");
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
}


void MainWindow::setTimersOnChecks()
{
    QObject::disconnect(&timer_on_updates, &QTimer::timeout, main_window_view, &MainWindowView::checkUpdates);
    QObject::disconnect(&timer_on_logs, &QTimer::timeout, Logger::logger(), &Logger::clearLogsFile);
    connectSignalForUpdateCheck();
    connectSignalForHistoryStore();
}


void MainWindow::startSystemTray()
{
    if (!main_window_view.isNull() && !system_tray_icon.isNull())
        disconnect(main_window_view, &MainWindowView::packagesToUpdateCountChanged, system_tray_icon.get(), &SystemTray::update);
    system_tray_icon.reset(nullptr);
    if (Settings::records()->useSystemTray())
    {
        system_tray_icon.reset(new SystemTray(this));
        connect(main_window_view, &MainWindowView::packagesToUpdateCountChanged, system_tray_icon.get(), &SystemTray::update);
    }
}


void MainWindow::startTimerOnOperation(const QDateTime& time, QTimer& timer,
                                       int time_limit_in_milliseconds, const QString& operation)
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
                               .arg(operation)
                               .arg(TimeConverter::timeToString(time_passed_in_milliseconds)));
}


void MainWindow::setAction(QPointer<QAction>& action,
                           QString text,
                           QString icon,
                           QKeySequence key_sequence)
{
    action = new QAction(this);
    action->setText(text);
    action->setIcon(QIcon::fromTheme(icon));
    this->actionCollection()->setDefaultShortcut(action, key_sequence);
    this->actionCollection()->addAction(icon, action);
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


void MainWindow::enableActions()
{
    update_action->setDisabled(false);
    refresh_action->setDisabled(false);
    download_action->setDisabled(false);
    update_all_action->setDisabled(false);
    update_mirrors_action->setDisabled(false);
    clean_action->setDisabled(false);
    print_statistics_action->setDisabled(false);
    search_action->setDisabled(false);
}


void MainWindow::settingsConfigure()
{
    QPointer<Settings> settings = new Settings(this);
    settings->show();
}
