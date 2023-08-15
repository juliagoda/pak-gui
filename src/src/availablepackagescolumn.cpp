// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of CachyOS package manager based on "pak" application.
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

#include "availablepackagescolumn.h"

#include "packagescolumn.h"
#include "sipackage.h"
#include "sicommandparser.h"
#include "logger.h"

#include <QListWidgetItem>
#include <QPointer>
#include <QMessageBox>


QMutex AvailablePackagesColumn::mutex;

AvailablePackagesColumn::AvailablePackagesColumn(QListWidget* new_list_widget,
                                                 QLineEdit* new_search_lineedit,
                                                 QCheckBox* new_reverse_sort_checkbox,
                                                 QWidget* new_parent) :
    PackagesColumn(new_list_widget, new_search_lineedit, new_reverse_sort_checkbox, new_parent)
{
    if (!search_lineedit)
        return;

    QObject::connect(search_lineedit, &QLineEdit::textChanged, packages_sorter.data(),
                     [&](const QString& text) { packages_sorter->sortPackagesByText<SiPackage>(text, SiPackage{""}); });
}


QStringList AvailablePackagesColumn::getPackagesList()
{
    QScopedPointer<SiCommandParser> command_parser(new SiCommandParser);
    return command_parser.data()->retrieveInfo();
}


void AvailablePackagesColumn::clearPackages()
{
    while (list_widget->item(0))
        delete dynamic_cast<SiPackage*>(list_widget->takeItem(0));

    list_widget->clear();
    list_widget->update();
}


void AvailablePackagesColumn::fill()
{
    mutex.lock();
    packages_sorter->resetOriginalList();
    Q_ASSERT(packages_sorter->isOriginalListEmpty());
    clearPackages();
    Q_ASSERT(list_widget->count() == 0);
    QStringList pak_packages = getPackagesList();
    int i = 0;

    std::for_each(pak_packages.begin(), pak_packages.end(), [this, &i](const QString& package)
    {
        auto package_item = new SiPackage(package);
        package_item->setNo(i+1);
        Q_ASSERT(package_item != nullptr);
        Q_ASSERT(list_widget != nullptr);
        list_widget->addItem(package_item);
        i++;
    });

    Logger::logger()->logInfo(QStringLiteral("Filled column with %1 available packages").arg(list_widget->count()));
    list_widget->update();
    mutex.unlock();
}


void AvailablePackagesColumn::clearForSort()
{
    QObject::disconnect(search_lineedit, &QLineEdit::textChanged, packages_sorter.data(), nullptr);
    packages_sorter->resetOriginalList();
}


void AvailablePackagesColumn::fillForSort()
{
    if (!search_lineedit)
        return;

    QObject::connect(search_lineedit, &QLineEdit::textChanged, packages_sorter.data(),
                     [&](const QString& text) { packages_sorter->sortPackagesByText<SiPackage>(text, SiPackage{""}); });
}
