/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef MAINWINDOWVIEW_H
#define MAINWINDOWVIEW_H

#include "ui_mainwindowview.h"

#include "availablepackagescolumn.h"
#include "installedpackagescolumn.h"
#include "updatedpackagescolumn.h"
#include "packagesmanager.h"

#include <QStringList>
#include <QSharedPointer>

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
    explicit MainWindowView(QWidget* parent);

    /**
     * Default Destructor
     */
    ~MainWindowView() override;

public Q_SLOTS:
    void switchColors();
    void handleSettingsChanged();

private:
    void fillColumns();
    void connectSignals();

    // this is the name of the root widget inside our Ui file
    // you can rename it in designer and then change it here
    Ui::MainWindowView m_ui;
    QPointer<AvailablePackagesColumn> available_packages_column;
    QPointer<InstalledPackagesColumn> installed_packages_column;
    QPointer<UpdatedPackagesColumn> updated_packages_column;
    QSharedPointer<PackagesManager> packages_manager;
};

#endif // MAINWINDOWVIEW_H
