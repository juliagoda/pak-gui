
#pragma once

#include "ui_mainwindowview.h"
#include "ui_packageinput.h"

#include "availablepackagescolumn.h"
#include "installedpackagescolumn.h"
#include "updatedpackagescolumn.h"
#include "progressview.h"
#include "process.h"
#include "actionsaccesschecker.h"
#include "spinninganimation.h"

#include <QStringList>
#include <QSharedPointer>
#include <QPointer>
#include <QThread>
#include <QMap>


class MainWindowView : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindowView(QSharedPointer<Process> new_process,
                            QSharedPointer<ActionsAccessChecker> new_actions_access_checker,
                            QWidget* parent);
    ~MainWindowView() override;

public Q_SLOTS:
    void refresh();
    void generatePreview(Process::Task task);
    void showStatisticsWindow();
    void downloadPackage();
    void finishProcess(Process::Task task, int exit_code, QProcess::ExitStatus exit_status);
    void checkUpdates();
    void updateWidgets();

private Q_SLOTS:
    void startAnimations();
    void connectSignalsForAvailablePackages();
    void connectSignalsForInstalledPackages();
    void connectSignalsForUpdatedPackages();
    void generateOutput(Process::Task task, const QString& line);
    void toggleWidgetsAccess(bool is_online);
    void startInternetCheckTimer();

signals:
    void operationsAmountIncreased();
    void initStarted();
    void initEnded();
    void availablePackagesFillEnded();
    void installedPackagesFillEnded();
    void packagesToUpdateFillEnded();
    void hideOnlineActions();
    void startOtherThreads();
    void packagesToUpdateCountChanged(int packages_count);

private:
    void setTimerOnActionsAccessChecker();
    void startCheckTimer(QPointer<QTimer> timer, int miliseconds, const QString& timer_type);
    void connectSignals();
    void hideWidgets();
    void hideWidgetsExceptInstalled();
    void init();
    void checkSpinningVisibility();
    void startPackagesCheckTimer();

    Ui::MainWindowView m_ui;
    QSharedPointer<Process> process;
    QSharedPointer<ActionsAccessChecker> actions_access_checker;
    QSharedPointer<AvailablePackagesColumn> available_packages_column;
    QSharedPointer<InstalledPackagesColumn> installed_packages_column;
    QSharedPointer<UpdatedPackagesColumn> updated_packages_column;
    QMap<Process::Task, QPointer<QWidget>> generated_previews_map;
    QSharedPointer<ProgressView> progress_view;
    QSharedPointer<SpinningAnimation> spinning_animation;
    QPointer<QTimer> internet_connection_timer;
};
