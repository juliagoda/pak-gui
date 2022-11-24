/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>
#include <QSharedPointer>
#include <QPointer>

#include "settings.h"
#include "process.h"
#include "actionsaccesschecker.h"

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
    MainWindow();
    ~MainWindow() override;

private Q_SLOTS:
    void settingsConfigure();
    void enableActions();
    void disableActions();
    void disableOnlineActions();

signals:
    void closeApp();

private:
    QAction* m_updateAction;
    QAction* m_refreshAction;
    QAction* m_downloadAction;
    QAction* m_printStatisticsAction;
    QAction* m_printVCSPackagesAction;
    QAction* m_updateAllAction;
    QAction* m_updateMirrorsAction;
    QAction* m_cleanAction;
    QAction* m_undoAction;
    QPointer<MainWindowView> main_window_view;
    QSharedPointer<Process> process;
    QSharedPointer<ActionsAccessChecker> actions_access_checker;
};

#endif // MAINWINDOW_H
