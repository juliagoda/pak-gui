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

#include <QStringList>
#include <QSharedPointer>
#include <QPointer>
#include <QThread>
#include <QMap>

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
    explicit MainWindowView(QSharedPointer<Process> new_process, QWidget* parent);
    ~MainWindowView() override;

public Q_SLOTS:
    void refresh();
    void switchColors();
    void handleSettingsChanged();
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

signals:
    void operationsAmountIncreased();
    void initStarted();
    void initEnded();
    void availablePackagesFillEnded();
    void installedPackagesFillEnded();
    void packagesToUpdateFillEnded();

private:
    void connectSignals();
    void hideWidgets();
    void init();
    void checkSpinningVisibility();

    // this is the name of the root widget inside our Ui file
    // you can rename it in designer and then change it here
    Ui::MainWindowView m_ui;
    QSharedPointer<Process> process;
    QSharedPointer<AvailablePackagesColumn> available_packages_column;
    QSharedPointer<InstalledPackagesColumn> installed_packages_column;
    QSharedPointer<UpdatedPackagesColumn> updated_packages_column;
    QMap<Process::Task, QPointer<QWidget>> generated_previews_map;
    QSharedPointer<ProgressView> progress_view;
    QSharedPointer<QMovie> spinning_animation;
};
