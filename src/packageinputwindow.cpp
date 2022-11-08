/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#include "packageinputwindow.h"
#include "qnamespace.h"

#include <QPushButton>
#include <QDialogButtonBox>


PackageInputWindow::PackageInputWindow(QWidget* parent)
    : QWidget(parent)
{
    m_ui.setupUi(this);

    m_ui.buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    connect(m_ui.package_lineedit, &QLineEdit::textEdited, this, &PackageInputWindow::toggleOkButton);
    connect(m_ui.buttonBox, &QDialogButtonBox::accepted, this, [this]() { emit packageNameInserted(m_ui.package_lineedit->text()); }, Qt::AutoConnection);
}

void PackageInputWindow::toggleOkButton(const QString& new_package_name)
{
   m_ui.buttonBox->button(QDialogButtonBox::Ok)->setDisabled(new_package_name.isEmpty());
}

