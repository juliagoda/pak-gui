#include "updatedpackagescolumn.h"

#include "logger.h"
#include "checkpackage.h"
#include "checkcommandparser.h"

#include <QPointer>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>
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

#include <KLocalizedString>


UpdatedPackagesColumn::UpdatedPackagesColumn(QListWidget* new_list_widget,
                                             QLineEdit* new_search_lineedit,
                                             QCheckBox* new_reverse_sort_checkbox,
                                             QWidget* new_parent) :
    PackagesColumn(new_list_widget, new_search_lineedit, new_reverse_sort_checkbox, new_parent),
    current_packages_count(0),
    parent(new_parent)
{
    if (!search_lineedit)
        return;

    QObject::connect(search_lineedit, &QLineEdit::textChanged, packages_sorter.data(),
                     [&](const QString& text) { packages_sorter->sortPackagesByText<CheckPackage>(text, CheckPackage{"", Package::Source::Unknown}); });
}


uint UpdatedPackagesColumn::getCurrentPackagesCount() const
{
    return current_packages_count;
}


QHash<QString, Package::Source> UpdatedPackagesColumn::getPackagesList()
{
    QSharedPointer<CheckCommandParser> command_parser(new CheckCommandParser);
    return command_parser.data()->retrieveInfoMap();
}


void UpdatedPackagesColumn::fill()
{
    packages_sorter->resetOriginalList();
    auto pak_packages = getPackagesList();
    updatePackagesCount(pak_packages.count());
    decltype(pak_packages)::iterator it = pak_packages.begin();
    int i = 0;

    for (;it != pak_packages.end(); it++)
    {
        CheckPackage* package_item = new CheckPackage(it.key(), it.value());
        package_item->setNo(i + 1);
        list_widget->insertItem(i, package_item);
        i++;
    }

    Logger::logger()->logInfo(QStringLiteral("Filled column with %1 packages to update").arg(list_widget->count()));
    list_widget->update();
}


void UpdatedPackagesColumn::toggleAllPackages(bool is_all_checked)
{
    for (int i = 0; i < list_widget->count(); ++i)
    {
        QListWidgetItem* item = list_widget->item(i);
        if (is_all_checked)
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked);
    }
}


template<> void UpdatedPackagesColumn::runAfterChoice<0>()
{
    toggleAllPackages(true);
    bool isAllChecked = getCheckedPackagesList().count() == list_widget->count();
    emit preparedList(getCheckedPackagesStringList(), isAllChecked ? Process::Task::UpdateAll : Process::Task::Update, getAurPackagesCount());
}


template<> void UpdatedPackagesColumn::runAfterChoice<1>()
{
    for (auto it = getCheckedPackagesList().begin(); it != getCheckedPackagesList().end(); it++)
    {
        if ((*it)->getSource() == Package::Source::AUR || (*it)->getSource() == Package::Source::POLAUR)
            (*it)->setCheckState(Qt::Unchecked);
    }
}


void UpdatedPackagesColumn::prepareBeforeProcessRun()
{
    int result = 2;

    if (getCheckedPackagesList().size() == 0)
    {
        Logger::logger()->logFatal(QString("Size of checked packages list is equal to 0. Abort prepareBeforeProcessRun()."));
        return;
    }

    auto first_package_source = getCheckedPackagesList().at(0)->getSource();
    bool containsSideSource = first_package_source == Package::Source::AUR || first_package_source == Package::Source::POLAUR;
    if (getCheckedPackagesList().count() != list_widget->count() && containsSideSource)
    {
        result = QMessageBox::warning(parent, i18n("Single AUR/POLAUR packages"), i18n("It's not possible to update single AUR/POLAUR packages"),
                                      i18n("Update all"), i18n("Uncheck these packages"), i18n("Cancel"));
    }

    if (result == 0)
        runAfterChoice<0>();
    if (result == 1)
        runAfterChoice<1>();
}


void UpdatedPackagesColumn::updatePackagesCount(uint new_current_packages_count)
{
    if (current_packages_count != new_current_packages_count)
        emit currentPackagesCountChanged(new_current_packages_count);

    current_packages_count = new_current_packages_count;
}


void UpdatedPackagesColumn::clearForSort()
{
    QObject::disconnect(search_lineedit, &QLineEdit::textChanged, packages_sorter.data(), nullptr);
    packages_sorter->resetOriginalList();
}
