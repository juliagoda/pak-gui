/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/
#pragma once

#include "ui_packageinput.h"

class PackageInputWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PackageInputWindow(QWidget* parent = nullptr);
    ~PackageInputWindow() override = default;

private Q_SLOTS:
    void toggleOkButton(const QString& new_package_name);

signals:
    void packageNameInserted(const QString& new_name);

private:
    Ui::PackageInputWindow m_ui;
};
