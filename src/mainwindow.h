#pragma once

#include <KXmlGuiWindow>
#include <QSharedPointer>
#include <QPointer>
#include <QTimer>

#include "settings.h"
#include "process.h"
#include "actionsaccesschecker.h"

class MainWindowView;

class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() override;

private Q_SLOTS:
    void settingsConfigure();
    void enableActions();
    void disableActions();
    void disableOnlineActions();
    void setTimersOnChecks();

signals:
    void closeApp();

private:
    void startTimerOnOperation(const QString& settings_value,
                               QTimer& timer,
                               int time_limit_in_milliseconds,
                               const QString& operation);

    QAction* m_updateAction;
    QAction* m_refreshAction;
    QAction* m_downloadAction;
    QAction* m_printStatisticsAction;
    QAction* m_printVCSPackagesAction;
    QAction* m_updateAllAction;
    QAction* m_updateMirrorsAction;
    QAction* m_cleanAction;
    QPointer<MainWindowView> main_window_view;
    QSharedPointer<Process> process;
    QSharedPointer<ActionsAccessChecker> actions_access_checker;
    QTimer timer_on_updates;
    QTimer timer_on_logs;
};
