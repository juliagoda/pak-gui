/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/
#pragma once

#include "ui_packageinput.h"

/**
 * This class serves as the main window for kde-example.  It handles the
 * menus, toolbars and status bars.
 *
 * @short Main window class
 * @author %{AUTHOR} <%{EMAIL}>
 * @version %{VERSION}
 */
class PackageInputWindow : public QWidget
{
    Q_OBJECT

public:
    /**
     * Default Constructor
     */
    explicit PackageInputWindow(QWidget* parent = nullptr);

    /**
     * Default Destructor
     */
    ~PackageInputWindow() override;

private Q_SLOTS:
    void toggleOkButton(const QString& new_package_name);

signals:
    bool packageNameInserted(const QString& new_name);

private:

    Ui::PackageInputWindow m_ui;
};
