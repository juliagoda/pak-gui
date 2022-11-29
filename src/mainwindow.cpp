

#include "mainwindow.h"

#include "actionsaccesschecker.h"
#include "mainwindowview.h"
#include "pakGuiSettings.h"
#include "timeconverter.h"
#include "logger.h"

#include <QAction>
#include <QStatusBar>

#include <KActionCollection>
#include <KConfigDialog>
#include <KLocalizedString>
#include <KStandardAction>


MainWindow::MainWindow()
    : KXmlGuiWindow(),
      process(QSharedPointer<Process>(new Process)),
      actions_access_checker(ActionsAccessChecker::actionsAccessChecker()),
      system_tray_icon(nullptr)
{
    main_window_view = new MainWindowView(process, actions_access_checker, this);
    setCentralWidget(main_window_view);
    setupSystemTrayIcon();
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

    setAction(download_action, i18n("&Download"), QString("download"), QKeySequence(Qt::CTRL, Qt::Key_D));
    connect(download_action, &QAction::triggered, main_window_view, &MainWindowView::downloadPackage);

    setAction(update_all_action, i18n("&Update all packages"), QString("updateAllPackages"), QKeySequence(Qt::CTRL, Qt::Key_U, Qt::Key_A));
    connect(update_all_action, &QAction::triggered, this, [this]() { process->run(Process::Task::UpdateAll); }, Qt::AutoConnection);

    setAction(update_mirrors_action, i18n("&Update mirrors"), QString("updateMirrors"), QKeySequence(Qt::CTRL, Qt::Key_U, Qt::Key_M));
    connect(update_mirrors_action, &QAction::triggered, this, [this]() { process->run(Process::Task::MirrorsUpdate); }, Qt::AutoConnection);

    setAction(clean_action, i18n("&Clean"), QString("clean"), QKeySequence(Qt::CTRL, Qt::Key_C));
    connect(clean_action, &QAction::triggered, this, [this]() { process->run(Process::Task::Clean); }, Qt::AutoConnection);

    setAction(print_statistics_action, i18n("&Statistics"), QString("statistics"), QKeySequence(Qt::CTRL, Qt::Key_S));
    connect(print_statistics_action, &QAction::triggered, main_window_view, &MainWindowView::showStatisticsWindow);

    setAction(print_vcs_packages_action, i18n("&Installed vcs packages"), QString("installedVcsPackages"), QKeySequence(Qt::CTRL, Qt::Key_P));
    connect(print_vcs_packages_action, &QAction::triggered, this, [this]() { process->run(Process::Task::PrintVCSPackages); }, Qt::AutoConnection);

    disableActions();

    KStandardAction::quit(qApp, SLOT(closeAllWindows()), actionCollection);
    KStandardAction::preferences(this, SLOT(settingsConfigure()), actionCollection);

    setupGUI(Default, "pak-gui.rc");
    setXMLFile("pak-gui.rc");
}


MainWindow::~MainWindow()
{

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
    print_vcs_packages_action->setDisabled(true);
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
    print_vcs_packages_action->setDisabled(false);
}


void MainWindow::setTimersOnChecks()
{
    QObject::connect(&timer_on_updates, &QTimer::timeout, main_window_view, &MainWindowView::checkUpdates);
    QObject::connect(&timer_on_logs, &QTimer::timeout, Logger::logger(), &Logger::clearLogsFile);
    startTimerOnOperation(QString("start_datetime_for_updates_check"),
                          timer_on_updates,
                          TimeConverter::toMilliseconds(pakGuiSettings::update_check_time_in_days(),
                                                        pakGuiSettings::update_check_time_in_hours(),
                                                        pakGuiSettings::update_check_time_in_minutes()),
                          QString("update"));
    startTimerOnOperation(QString("start_datetime_for_history_store"),
                          timer_on_logs,
                          TimeConverter::daysToMilliseconds(pakGuiSettings::history_store_time_in_days()),
                          QString("logs remove"));
}


void MainWindow::startTimerOnOperation(const QString& settings_value, QTimer& timer,
                                       int time_limit_in_milliseconds, const QString& operation)
{
    QDateTime init_datetime = Settings::getDateTime(settings_value);
    if (!init_datetime.isValid() || time_limit_in_milliseconds == 0)
        return;

    qint64 time_passed_in_milliseconds = init_datetime.msecsTo(QDateTime::currentDateTime());
    if (time_passed_in_milliseconds > time_limit_in_milliseconds)
    {
        Logger::logger()->logDebug(QStringLiteral("Restart timer for %1").arg(operation));
        timer.start(time_limit_in_milliseconds);
    }
    else
    {
        timer.start(time_limit_in_milliseconds - time_passed_in_milliseconds);
    }

    Logger::logger()->logDebug(QStringLiteral("Time passed for %1: %2")
                               .arg(operation)
                               .arg(TimeConverter::timeToString(time_passed_in_milliseconds)));
}


void MainWindow::setupSystemTrayIcon()
{
    if (!pakGuiSettings::use_system_tray_icon())
        return;

    system_tray_icon.reset(new KStatusNotifierItem(this));
    system_tray_icon->setStandardActionsEnabled(true);
    system_tray_icon->setAssociatedWidget(this);
    system_tray_icon->setIconByName(QStringLiteral("pak-gui"));
    system_tray_icon->setStatus(KStatusNotifierItem::Passive);
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


void MainWindow::enableActions()
{
    update_action->setDisabled(false);
    refresh_action->setDisabled(false);
    download_action->setDisabled(false);
    update_all_action->setDisabled(false);
    update_mirrors_action->setDisabled(false);
    clean_action->setDisabled(false);
    print_statistics_action->setDisabled(false);
    print_vcs_packages_action->setDisabled(false);
}


void MainWindow::settingsConfigure()
{
    QPointer<Settings> settings_window = new Settings(this);
    settings_window->show();
}
