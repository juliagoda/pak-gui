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

#pragma once

#include "packagescolumn.h"
#include "process.h"

#include <QStringList>
#include <QHash>


class UpdatedPackagesColumn : public PackagesColumn
{
    Q_OBJECT

public:
    UpdatedPackagesColumn(QListWidget* new_list_widget,
                          QLineEdit* new_search_lineedit,
                          QCheckBox* new_reverse_sort_checkbox,
                          QWidget* new_parent);
    uint getCurrentPackagesCount() const;
    void fill() override;
    void clearForSort();

public Q_SLOTS:
    void toggleAllPackages(bool is_all_checked);
    void prepareBeforeProcessRun();

protected:
    virtual QHash<QString, Package::Source> getPackagesList();

signals:
    void currentPackagesCountChanged(int new_current_packages_count);
    void chosenUpdateAll();
    void chosenUncheckSidePackages();
    void preparedList(QStringList packages, Process::Task, uint aur_checked_packages);

private:
    void updatePackagesCount(uint new_current_packages_count);

    template<int> void runAfterChoice();

    uint current_packages_count;
    QWidget* parent;
};

