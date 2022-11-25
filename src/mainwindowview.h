/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#pragma once

#include "ui_mainwindowview.h"
#include "ui_packageinput.h"

#include "availablepackagescolumn.h"
#include "installedpackagescolumn.h"
#include "updatedpackagescolumn.h"
#include "progressview.h"
#include "process.h"
#include "actionsaccesschecker.h"

#include <QStringList>
#include <QSharedPointer>
#include <QPointer>
#include <QThread>
#include <QMap>
#include <QMovie>

/**
 * This class serves as the main window for kde-example.  It handles the
 * menus, toolbars and status bars.
 *
 * @short Main window class
 * @author %{AUTHOR} <%{EMAIL}>
 * @version %{VERSION}
 */
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

private Q_SLOTS:
    void showAnimation();
    void stopAnimation();
    void connectSignalsForAvailablePackages();
    void connectSignalsForInstalledPackages();
    void connectSignalsForUpdatedPackages();
    void generateOutput(Process::Task task, const QString& line);
    void toggleWidgetsAccess(bool is_online);

signals:
    void operationsAmountIncreased();
    void initStarted();
    void initEnded();
    void availablePackagesFillEnded();
    void installedPackagesFillEnded();
    void packagesToUpdateFillEnded();
    void hideOnlineActions();
    void startOtherThreads();

private:
    void setTimerOnActionsAccessChecker();
    void connectSignals();
    void hideWidgets();
    void hideWidgetsExceptInstalled();
    void init();
    void checkSpinningVisibility();

    Ui::MainWindowView m_ui;
    QSharedPointer<Process> process;
    QSharedPointer<ActionsAccessChecker> actions_access_checker;
    QSharedPointer<AvailablePackagesColumn> available_packages_column;
    QSharedPointer<InstalledPackagesColumn> installed_packages_column;
    QSharedPointer<UpdatedPackagesColumn> updated_packages_column;
    QMap<Process::Task, QPointer<QWidget>> generated_previews_map;
    QSharedPointer<ProgressView> progress_view;
    QSharedPointer<QMovie> spinning_animation;
};
