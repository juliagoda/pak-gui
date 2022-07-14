/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// application headers
#include "mainwindowview.h"

#include "pakGuiSettings.h"

#include <KLocalizedString>


MainWindowView::MainWindowView(QWidget *parent)
    : QWidget(parent)
{
    m_ui.setupUi(this);
    handleSettingsChanged();
}

MainWindowView::~MainWindowView()
{
}

void MainWindowView::switchColors()
{
    // switch the foreground/background colors of the label
    QColor color = pakGuiSettings::colorBackground();
    pakGuiSettings::setColorBackground(pakGuiSettings::colorForeground());
    pakGuiSettings::setColorForeground(color);

    handleSettingsChanged();
}

void MainWindowView::handleSettingsChanged()
{
    QPalette palette = m_ui.templateLabel->palette();
    palette.setColor(QPalette::Window, pakGuiSettings::colorBackground());
    palette.setColor(QPalette::WindowText, pakGuiSettings::colorForeground());
    m_ui.templateLabel->setPalette(palette);

    // i18n : internationalization
    m_ui.templateLabel->setText(i18n("This project is %1 days old", pakGuiSettings::ageInDays()));
}

