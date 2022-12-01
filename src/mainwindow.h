#pragma once

#include <KXmlGuiWindow>
#include <QSharedPointer>
#include <QScopedPointer>
#include <QPointer>
#include <QTimer>
#include <QKeySequence>

#include "process.h"
#include "actionsaccesschecker.h"
#include "systemtray.h"


class MainWindowView;

class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() override;

public Q_SLOTS:
    void startSystemTray();
    void setTimersOnChecks();

private Q_SLOTS:
    void settingsConfigure();
    void enableActions();
    void disableActions();
    void disableOnlineActions();

signals:
    void closeApp();
    void widgetsChanged();
    void updatedPackageInfoList();

private:
    void startTimerOnOperation(const QDateTime& time,
                               QTimer& timer,
                               int time_limit_in_milliseconds,
                               const QString& operation);
    void setAction(QPointer<QAction>& action,
                   QString text,
                   QString icon,
                   QKeySequence key_sequence);
    void connectSignalForUpdateCheck();
    void connectSignalForHistoryStore();

    QTimer timer_on_updates;
    QTimer timer_on_logs;
    QPointer<QAction> update_action;
    QPointer<QAction> refresh_action;
    QPointer<QAction> download_action;
    QPointer<QAction> print_statistics_action;
    QPointer<QAction> print_vcs_packages_action;
    QPointer<QAction> update_all_action;
    QPointer<QAction> update_mirrors_action;
    QPointer<QAction> clean_action;
    QPointer<MainWindowView> main_window_view;
    QSharedPointer<Process> process;
    QSharedPointer<ActionsAccessChecker> actions_access_checker;
    QScopedPointer<SystemTray> system_tray_icon;
};
