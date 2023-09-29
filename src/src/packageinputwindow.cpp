// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of  package manager based on "pak" application.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "packageinputwindow.h"

#include "logger.h"

#include <QPushButton>
#include <QDialogButtonBox>


PackageInputWindow::PackageInputWindow(QWidget* parent)
    : QWidget(parent)
{
    m_ui.setupUi(this);
    setWindowTitle(i18n("Package input"));
    m_ui.buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    connect(m_ui.package_lineedit, &QLineEdit::textEdited, this, &PackageInputWindow::toggleOkButton);
    connect(m_ui.buttonBox, &QDialogButtonBox::accepted, this, [this]() { emit packageNameInserted(m_ui.package_lineedit->text()); }, Qt::AutoConnection);
    connect(m_ui.buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, [this]() { emit cancelled(); }, Qt::AutoConnection);
}


void PackageInputWindow::toggleOkButton(const QString& new_package_name)
{
    auto ok_button = m_ui.buttonBox->button(QDialogButtonBox::Ok);
    ok_button->setEnabled(!new_package_name.isEmpty());
    Logger::logger()->logDebug(new_package_name.isEmpty() ? "Package name is empty" : "Package name is not empty");
    Logger::logger()->logDebug(ok_button->isEnabled() ? "OK button is now enabled" : "OK button is now disabled");
}

