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

#include "installedpackagescolumn.h"

#include "qipackage.h"
#include "qicommandparser.h"
#include "logger.h"

#include <QListWidgetItem>
#include <QPointer>
#include <QMessageBox>


InstalledPackagesColumn::InstalledPackagesColumn(QListWidget* new_list_widget,
                                                 QLineEdit* new_search_lineedit,
                                                 QCheckBox* new_reverse_sort_checkbox,
                                                 QWidget* new_parent) :
    PackagesColumn(new_list_widget, new_search_lineedit, new_reverse_sort_checkbox, new_parent)
{
    if (!search_lineedit)
        return;

    QObject::connect(search_lineedit, &QLineEdit::textChanged, packages_sorter.data(),
        [&](const QString& text) { packages_sorter->sortPackagesByText<QiPackage>(text, QiPackage{""}); });
}


QStringList InstalledPackagesColumn::getPackagesList()
{
    QScopedPointer<QiCommandParser> command_parser(new QiCommandParser);
    QObject::connect(command_parser.get(), &QiCommandParser::processStarted, [this](QProcess* process){ emit showAbortButton(process); });
    QObject::connect(command_parser.get(), &QiCommandParser::processEnded, [this](){ emit hideAbortButton(); });
    const auto& info = command_parser->retrieveInfo();
    QObject::disconnect(command_parser.get(), &QiCommandParser::processStarted, nullptr, nullptr);
    QObject::disconnect(command_parser.get(), &QiCommandParser::processEnded, nullptr, nullptr);
    return info;
}


void InstalledPackagesColumn::clearPackages()
{
    if (!list_widget)
        return;

    while (list_widget->item(0))
        delete list_widget->takeItem(0);

    list_widget->clear();
    list_widget->update();
}


void InstalledPackagesColumn::fill()
{
    mutex.lock();

#ifdef RUN_TESTS
    QDeadlineTimer deadline(getWaitTime());
    condition.wait(&mutex, deadline);
#else
    condition.wait(&mutex);
#endif

    packages_sorter->resetOriginalList();
    Q_ASSERT(packages_sorter->isOriginalListEmpty());
    clearPackages();
    Q_ASSERT(list_widget->count() == 0);
    const QStringList& pak_packages = getPackagesList();
    int i = 0;

    std::for_each(pak_packages.begin(), pak_packages.end(), [this, &i](const QString& package)
    {
        QiPackage* package_item = new QiPackage(package);
        package_item->setNo(i + 1);
        Q_ASSERT(package_item != nullptr);
        Q_ASSERT(list_widget != nullptr);
        list_widget->addItem(package_item);
        i++;
    });

    Logger::logger()->logInfo(QStringLiteral("Filled column with %1 installed packages").arg(list_widget->count()));
    list_widget->update();
    mutex.unlock();
}


void InstalledPackagesColumn::clearForSort()
{
    QObject::disconnect(search_lineedit, &QLineEdit::textChanged, packages_sorter.data(), nullptr);
    packages_sorter->resetOriginalList();
}


void InstalledPackagesColumn::fillForSort()
{
    if (!search_lineedit)
        return;

    QObject::connect(search_lineedit, &QLineEdit::textChanged, packages_sorter.data(),
                     [&](const QString& text) { packages_sorter->sortPackagesByText<QiPackage>(text, QiPackage{""}); });
}
