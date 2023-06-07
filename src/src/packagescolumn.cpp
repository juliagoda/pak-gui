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

#include "packagescolumn.h"

#include "logger.h"


PackagesColumn::PackagesColumn(QListWidget* new_list_widget,
                               QLineEdit* new_search_lineedit,
                               QCheckBox* new_reverse_sort_checkbox,
                               QWidget* new_parent) :
    QObject(),
    checked_packages(0),
    aur_checked_packages(0),
    list_widget(new_list_widget),
    search_lineedit(new_search_lineedit),
    packages_sorter(new Sorter(list_widget, new_reverse_sort_checkbox), &QObject::deleteLater),
    parent(new_parent),
    checked_packages_list()
{
    if (!list_widget)
        return;

    QObject::connect(list_widget, &QListWidget::itemChanged, this, &PackagesColumn::countCheckedPackages);
    QObject::connect(list_widget, &QListWidget::itemChanged, packages_sorter.get(), &Sorter::setCheckStateForUnsortedList);
}


void PackagesColumn::fill()
{
   // ...
}


void PackagesColumn::clear()
{
    checked_packages_list.clear();
    checked_packages = 0;
    aur_checked_packages = 0;
    list_widget->clear();
    list_widget->update();
}


QList<Package*> PackagesColumn::getCheckedPackagesList() const
{
    return checked_packages_list;
}


uint PackagesColumn::getAurPackagesCount() const
{
    return aur_checked_packages;
}


QStringList PackagesColumn::getCheckedPackagesStringList()
{
    QStringList checked_packages;
    decltype(checked_packages_list)::iterator it;
    for (it = checked_packages_list.begin(); it != checked_packages_list.end(); it++)
    {
        if (!(*it))
        {
            checked_packages_list.removeOne((*it));
            continue;
        }

        checked_packages.append((*it)->getName());
    }

    return checked_packages;
}


void PackagesColumn::update(int exit_code,
                            QProcess::ExitStatus exit_status,
                            const QString& warning_title,
                            const QString& action_verb)
{
    Q_UNUSED(exit_code)

    if (exit_status == QProcess::ExitStatus::CrashExit)
    {
        QMessageBox::warning(parent, warning_title,
                             tr("Packages couln't be %1\n"
                                "Do you want to see logs?").arg(action_verb),
                             QMessageBox::Yes | QMessageBox::Cancel);
        return;
    }

    list_widget->clear();
    fill();
    list_widget->update();
}


void PackagesColumn::sort(bool is_sorted)
{
    Q_UNUSED(is_sorted)
    QtConcurrent::run(packages_sorter.get(), &Sorter::sortReverse);
    list_widget->update();
}


void PackagesColumn::countCheckedPackages(QListWidgetItem* item)
{
    Package* package = dynamic_cast<Package*>(item);
    if (package->checkState() == Qt::Checked)
        addCheckedPackage(package);
    else
        removeUncheckedPackage(package);

    emit checkedPackagesCounterChanged(checked_packages_list.count() > 0);
}


void PackagesColumn::addCheckedPackage(Package* package)
{
    if (package->getSource() == Package::Source::AUR ||
        package->getSource() == Package::Source::POLAUR)
    {
        aur_checked_packages++;
        checked_packages_list.prepend(package);
        Logger::logger()->logDebug(QStringLiteral("Added at the beginning of list package: %1").arg(package->getName()));
        return;
    }

    checked_packages_list.append(package);
    Logger::logger()->logDebug(QStringLiteral("Added at the end of list package: %1").arg(package->getName()));
}


void PackagesColumn::removeUncheckedPackage(Package* package)
{
    int index = checked_packages_list.indexOf(package);
    if (package->getSource() == Package::Source::AUR)
        aur_checked_packages--;

    checked_packages_list.removeAt(index);
    Logger::logger()->logDebug(QStringLiteral("Removed package name from list: %1 - index: %2").arg(package->getName(), index));
}
