/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>

#include "ui_settings.h"
#include "pakGuiSettings.h"

class MainWindowView;

/**
 * This class serves as the main window for pak-gui.  It handles the
 * menus, toolbars and status bars.
 *
 * @short Main window class
 * @author %{AUTHOR} <%{EMAIL}>
 * @version %{VERSION}
 */
class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    MainWindow();

    /**
     * Default Destructor
     */
    ~MainWindow() override;

private Q_SLOTS:
    /**
     * Create a new window
     */
    void fileNew();

    /**
     * Open the settings dialog
     */
    void settingsConfigure();

private:
    // this is the name of the root widget inside our Ui file
    // you can rename it in designer and then change it here
    Ui::Settings m_settings;
    QAction* m_switchAction;
    QAction* m_updateAction;
    QAction* m_refreshAction;
    QAction* m_searchAction;
    QAction* m_downloadAction;
    QAction* m_printStatisticsAction;
    QAction* m_printNewsAction;
    QAction* m_printVCSPackagesAction;
    QAction* m_updateAllAction;
    QAction* m_updateMirrorsAction;
    QAction* m_cleanAction;
    QAction* m_undoAction;
    MainWindowView* mainWindowView;
};

#endif // MAINWINDOW_H
