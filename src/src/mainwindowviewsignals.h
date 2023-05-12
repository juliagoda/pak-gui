#pragma once

#include "src/mainwindowview.h"

#include <QThread>


class MainWindowViewSignals : public QObject
{
    Q_OBJECT
public:
    explicit MainWindowViewSignals(MainWindowView* main_window_view);

    void attachInputAnswerLines();
    void attachFillColumns(QThread* available_packages_thread, QThread* installed_packages_thread);
    void startPackagesCheckTimer();
    virtual void startInternetCheckTimer();
    void initSignals();
    void initColumns();
    void attachCheckUpdates(QThread* updated_packages_thread);

private:
    void attachConnectSignalsAfterFillEnd();
    void attachMainPreviewsVisibility();
    void attachPackagesAccess();
    void attachSignalsForSidePreviews();
    void attachSignalsForProcess();
    void attachAvailablePackagesColumn();
    void attachInstalledPackagesColumn();
    void attachPackagesToUpdateColumn();

    MainWindowView* main_window_view;
};

