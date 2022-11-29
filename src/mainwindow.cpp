

#include "mainwindow.h"

#include "actionsaccesschecker.h"
#include "mainwindowview.h"
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
      actions_access_checker(ActionsAccessChecker::actionsAccessChecker())
{
    main_window_view = new MainWindowView(process, actions_access_checker, this);
    setCentralWidget(main_window_view);

    QObject::connect(actions_access_checker.get(), &ActionsAccessChecker::requiredPackagesNotFound, [this]() { emit closeApp(); });

    Settings::saveInitDateTimesWhenEmpty();
    setTimersOnChecks();

    KActionCollection* actionCollection = this->actionCollection();

    m_updateAction = new QAction(this);
    m_updateAction->setText(i18n("&Update"));
    m_updateAction->setIcon(QIcon::fromTheme("update"));
    actionCollection->setDefaultShortcut(m_updateAction, Qt::CTRL + Qt::Key_U);
    actionCollection->addAction("update", m_updateAction);
    connect(m_updateAction, &QAction::triggered, this, [this]() { process->run(Process::Task::UpdateInstalledPackages); }, Qt::AutoConnection);

    m_refreshAction = new QAction(this);
    m_refreshAction->setText(i18n("&Refresh"));
    m_refreshAction->setIcon(QIcon::fromTheme("refresh"));
    actionCollection->setDefaultShortcut(m_refreshAction, Qt::CTRL + Qt::Key_R);
    actionCollection->addAction("refresh", m_refreshAction);
    connect(m_refreshAction, &QAction::triggered, main_window_view, &MainWindowView::refresh);
    connect(main_window_view, &MainWindowView::initStarted, this, &MainWindow::disableActions);
    connect(main_window_view, &MainWindowView::initEnded, this, &MainWindow::enableActions);
    connect(main_window_view, &MainWindowView::hideOnlineActions, this, &MainWindow::disableOnlineActions);

    m_downloadAction = new QAction(this);
    m_downloadAction->setText(i18n("&Download"));
    m_downloadAction->setIcon(QIcon::fromTheme("download"));
    actionCollection->setDefaultShortcut(m_downloadAction, Qt::CTRL + Qt::Key_D);
    actionCollection->addAction("download", m_downloadAction);
    connect(m_downloadAction, &QAction::triggered, main_window_view, &MainWindowView::downloadPackage);

    m_updateAllAction = new QAction(this);
    m_updateAllAction->setText(i18n("&Update all packages"));
    m_updateAllAction->setIcon(QIcon::fromTheme("updateAllPackages"));
    actionCollection->setDefaultShortcut(m_updateAllAction, Qt::CTRL + Qt::Key_U + Qt::Key_A);
    actionCollection->addAction("updateAllPackages", m_updateAllAction);
    connect(m_updateAllAction, &QAction::triggered, this, [this]() { process->run(Process::Task::UpdateAll); }, Qt::AutoConnection);

    m_updateMirrorsAction = new QAction(this);
    m_updateMirrorsAction->setText(i18n("&Update mirrors"));
    m_updateMirrorsAction->setIcon(QIcon::fromTheme("updateMirrors"));
    actionCollection->setDefaultShortcut(m_updateMirrorsAction, Qt::CTRL + Qt::Key_U + Qt::Key_M);
    actionCollection->addAction("updateMirrors", m_updateMirrorsAction);
    connect(m_updateMirrorsAction, &QAction::triggered, this, [this]() { process->run(Process::Task::MirrorsUpdate); }, Qt::AutoConnection);

    m_cleanAction = new QAction(this);
    m_cleanAction->setText(i18n("&Clean"));
    m_cleanAction->setIcon(QIcon::fromTheme("clean"));
    actionCollection->setDefaultShortcut(m_cleanAction, Qt::CTRL + Qt::Key_C);
    actionCollection->addAction(i18n("clean"), m_cleanAction);
    connect(m_cleanAction, &QAction::triggered, this, [this]() { process->run(Process::Task::Clean); }, Qt::AutoConnection);

    m_printStatisticsAction = new QAction(this);
    m_printStatisticsAction->setText(i18n("&Statistics"));
    m_printStatisticsAction->setIcon(QIcon::fromTheme("statistics"));
    actionCollection->setDefaultShortcut(m_printStatisticsAction, Qt::CTRL + Qt::Key_S);
    actionCollection->addAction("statistics", m_printStatisticsAction);
    connect(m_printStatisticsAction, &QAction::triggered, main_window_view, &MainWindowView::showStatisticsWindow);

    m_printVCSPackagesAction = new QAction(this);
    m_printVCSPackagesAction->setText(i18n("&Installed vcs packages"));
    m_printVCSPackagesAction->setIcon(QIcon::fromTheme("installedVcsPackages"));
    actionCollection->setDefaultShortcut(m_printVCSPackagesAction, Qt::CTRL + Qt::Key_P);
    actionCollection->addAction("installedVcsPackages", m_printVCSPackagesAction);
    connect(m_printVCSPackagesAction, &QAction::triggered, this, [this]() { process->run(Process::Task::PrintVCSPackages); }, Qt::AutoConnection);

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
    m_updateAction->setDisabled(true);
    m_refreshAction->setDisabled(true);
    m_downloadAction->setDisabled(true);
    m_updateAllAction->setDisabled(true);
    m_updateMirrorsAction->setDisabled(true);
    m_cleanAction->setDisabled(true);
    m_printStatisticsAction->setDisabled(true);
    m_printVCSPackagesAction->setDisabled(true);
}


void MainWindow::disableOnlineActions()
{
    m_updateAction->setDisabled(true);
    m_downloadAction->setDisabled(true);
    m_updateAllAction->setDisabled(true);
    m_updateMirrorsAction->setDisabled(true);
    m_refreshAction->setDisabled(false);
    m_cleanAction->setDisabled(false);
    m_printStatisticsAction->setDisabled(false);
    m_printVCSPackagesAction->setDisabled(false);
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


void MainWindow::enableActions()
{
    m_updateAction->setDisabled(false);
    m_refreshAction->setDisabled(false);
    m_downloadAction->setDisabled(false);
    m_updateAllAction->setDisabled(false);
    m_updateMirrorsAction->setDisabled(false);
    m_cleanAction->setDisabled(false);
    m_printStatisticsAction->setDisabled(false);
    m_printVCSPackagesAction->setDisabled(false);
}


void MainWindow::settingsConfigure()
{
    QPointer<Settings> settings_window = new Settings(this);
    settings_window->show();
}
