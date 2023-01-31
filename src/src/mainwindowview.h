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
#include <QWidget>
#include <QPointer>
#include <QThread>
#include <QMap>

namespace Ui {
class MainWindowView;
}

class MainWindowView : public QWidget
{
    Q_OBJECT

    Q_SLOT void generateOutput(Process::Task task, const QString& line);
public:
    explicit MainWindowView(QWidget* parent = nullptr);
    ~MainWindowView() = default;
    void setProcess(QSharedPointer<Process> new_process);
    void setActionsAccessChecker(QSharedPointer<ActionsAccessChecker> new_actions_access_checker);
    void init();
    virtual void run();
    void preparePreviews();

public Q_SLOTS:
    void refresh();
    void generatePreview(Process::Task task);
    void showStatisticsWindow();
    void downloadPackage();
    void searchPackage();
    void finishProcess(Process::Task task, int exit_code, QProcess::ExitStatus exit_status);
    virtual void checkUpdates();
    void updateWidgets();
    void checkRunningThreadsBeforeQuit();

private Q_SLOTS:
    void startAnimations();
    void connectSignalsForAvailablePackages();
    void connectSignalsForInstalledPackages();
    void connectSignalsForUpdatedPackages();
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

protected:
    Ui::MainWindowView m_ui;
    QSharedPointer<AvailablePackagesColumn> available_packages_column;
    QSharedPointer<InstalledPackagesColumn> installed_packages_column;
    QSharedPointer<UpdatedPackagesColumn> updated_packages_column;
    QSharedPointer<SpinningAnimation> spinning_animation;
    QMap<Process::Task, QPointer<QWidget>> generated_previews_map;
    QSharedPointer<ProgressView> progress_view;

    virtual void showFinishInformation();

private:
    void stopRunningThread(QSharedPointer<QThread> &thread);
    void setTimerOnActionsAccessChecker();
    void startCheckTimer(QPointer<QTimer> timer, int miliseconds, const QString& timer_type);
    void connectSignals();
    void hideWidgets();
    void hideWidgetsExceptInstalled();
    void checkSpinningVisibility();
    void startPackagesCheckTimer();
    void initSignals();
    void initColumns();
    void updatePreviewsDesign();

    QSharedPointer<Process> process;
    QSharedPointer<ActionsAccessChecker> actions_access_checker;
    QPointer<QTimer> internet_connection_timer;
    bool is_operation_running;
};
