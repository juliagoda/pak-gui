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
    /**
     * Default Constructor
     */
    explicit MainWindowView(QSharedPointer<Process> new_process, QWidget* parent);

    /**
     * Default Destructor
     */
    ~MainWindowView() override;

public Q_SLOTS:
    void refresh();
    void switchColors();
    void handleSettingsChanged();
    void generatePreview(Process::Task task);
    void showStatisticsWindow();
    void downloadPackage();
    void finishProcess(Process::Task task, int exit_code, QProcess::ExitStatus exit_status);

signals:
    void operationsAmountIncreased();

private:
    void connectSignals();
    void connectSignalsForAvailablePackages();
    void connectSignalsForInstalledPackages();
    void connectSignalsForUpdatedPackages();
    void hideWidgets();

    // this is the name of the root widget inside our Ui file
    // you can rename it in designer and then change it here
    Ui::MainWindowView m_ui;
    QSharedPointer<Process> process;
    QPointer<AvailablePackagesColumn> available_packages_column;
    QPointer<InstalledPackagesColumn> installed_packages_column;
    QPointer<UpdatedPackagesColumn> updated_packages_column;
    QThread* available_packages_thread;
    QThread* installed_packages_thread;
    QThread* updated_packages_thread;
    QMap<Process::Task, QPointer<QWidget>> generated_previews_map;
    QSharedPointer<ProgressView> progress_view;
};
