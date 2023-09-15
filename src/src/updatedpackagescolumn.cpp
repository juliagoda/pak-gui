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

#include "updatedpackagescolumn.h"

#include "logger.h"
#include "checkpackage.h"
#include "checkcommandparser.h"

#include <QPointer>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>

#include <KLocalizedString>

#include <algorithm>


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
    QObject::connect(command_parser.get(), &CheckCommandParser::processStarted, [this](QProcess* process){ emit showAbortButton(process); });
    QObject::connect(command_parser.get(), &CheckCommandParser::processEnded, [this](){ emit hideAbortButton(); });
    const auto& info = command_parser->retrieveInfoMap();
    QObject::disconnect(command_parser.get(), &CheckCommandParser::processStarted, nullptr, nullptr);
    QObject::disconnect(command_parser.get(), &CheckCommandParser::processEnded, nullptr, nullptr);
    return info;
}


void UpdatedPackagesColumn::fill()
{
    mutex.lock();
    packages_sorter->resetOriginalList();
    Q_ASSERT(packages_sorter->isOriginalListEmpty());
    clearPackages();
    Q_ASSERT(list_widget->count() == 0);
    const auto& pak_packages = getPackagesList();
    updatePackagesCount(pak_packages.count());
    wakeUpOtherColumns();
    QHash<QString, Package::Source>::const_iterator it = pak_packages.cbegin();
    int i = 0;

    for (;it != pak_packages.cend(); it++)
    {
        if ((it.key()).count("=>") > 1)
        {
            i++;
            continue;
        }

        CheckPackage* package_item = new CheckPackage(it.key(), it.value());
        package_item->setNo(i + 1);
        Q_ASSERT(package_item != nullptr);
        Q_ASSERT(list_widget != nullptr);
        list_widget->addItem(package_item);
        i++;
    }

    Logger::logger()->logInfo(QStringLiteral("Filled column with %1 packages to update").arg(list_widget->count()));
    list_widget->update();
    mutex.unlock();
}


void UpdatedPackagesColumn::toggleAllPackages(bool is_all_checked)
{
    for (int i = 0; i < list_widget->count(); ++i)
    {
        QListWidgetItem* item = list_widget->item(i);
        item->setCheckState(is_all_checked ? Qt::Checked : Qt::Unchecked);
    }
}


template<> void UpdatedPackagesColumn::runAfterChoice<0>()
{
    toggleAllPackages(true);
}


template<> void UpdatedPackagesColumn::runAfterChoice<1>()
{
    std::size_t limit = checked_packages_list.size();
    for(std::size_t i = 0; i < limit; i++)
    {
        if (checked_packages_list[0]->getSource() == Package::Source::AUR ||
            checked_packages_list[0]->getSource() == Package::Source::POLAUR)
        {
            checked_packages_list[0]->setCheckState(Qt::Unchecked);
        }
    }
}


void UpdatedPackagesColumn::prepareBeforeProcessRun()
{
    int result = 3;

    if (getCheckedPackagesList().size() == 0)
    {
        Logger::logger()->logFatal(QString("Size of checked packages list is equal to 0. Abort prepareBeforeProcessRun()."));
        return;
    }

    auto first_package_source = getCheckedPackagesList().at(0)->getSource();
    bool containsSideSource = first_package_source == Package::Source::AUR || first_package_source == Package::Source::POLAUR;
    if (static_cast<int>(getCheckedPackagesList().size()) != list_widget->count() && containsSideSource)
    {
        result = QMessageBox::warning(parent, i18n("Single AUR/POLAUR packages"), i18n("It's not possible to update single AUR/POLAUR packages"),
                                      i18n("Update all"), i18n("Uncheck these packages"), i18n("Cancel"));
    }

    if (result == 0)
        runAfterChoice<0>();
    if (result == 1)
        runAfterChoice<1>();
    if (result != 2 && !checked_packages_list.empty())
    {
        bool isAllChecked = static_cast<int>(getCheckedPackagesList().size()) == list_widget->count();
        emit preparedList(getCheckedPackagesStringList(), isAllChecked ? Process::Task::UpdateAll : Process::Task::Update, getAurPackagesCount());
    }
}


void UpdatedPackagesColumn::updatePackagesCount(uint new_current_packages_count)
{
    emit currentPackagesCountChanged(new_current_packages_count);

    current_packages_count = new_current_packages_count;
}


void UpdatedPackagesColumn::clearPackages()
{
    if (!list_widget)
        return;

    while (list_widget->item(0))
        delete list_widget->takeItem(0);

    list_widget->clear();
    list_widget->update();
}


void UpdatedPackagesColumn::wakeUpOtherColumns()
{
   condition.wakeAll();
}


void UpdatedPackagesColumn::clearForSort()
{
    QObject::disconnect(search_lineedit, &QLineEdit::textChanged, packages_sorter.data(), nullptr);
    packages_sorter->resetOriginalList();
}


void UpdatedPackagesColumn::fillForSort()
{
    if (!search_lineedit)
        return;

    QObject::connect(search_lineedit, &QLineEdit::textChanged, packages_sorter.data(),
    [&](const QString& text) { packages_sorter->sortPackagesByText<CheckPackage>(text, CheckPackage{"", Package::Source::Unknown}); });
}
