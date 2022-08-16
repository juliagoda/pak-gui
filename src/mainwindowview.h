/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef MAINWINDOWVIEW_H
#define MAINWINDOWVIEW_H

#include "ui_mainwindowview.h"

#include <QStringList>

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

    // this is the name of the root widget inside our Ui file
    // you can rename it in designer and then change it here
    Ui::MainWindowView m_ui;
};

#endif // MAINWINDOWVIEW_H
