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

#pragma once

#include "sorter.h"

#include <QLineEdit>
#include <QListWidget>
#include <QProcess>
#include <QStringList>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>
#include <QWaitCondition>

#include <deque>


class PackagesColumn : public QObject
{
    Q_OBJECT

public:
    PackagesColumn(QListWidget* new_list_widget,
                   QLineEdit* new_search_lineedit,
                   QCheckBox* new_reverse_sort_checkbox,
                   QWidget* new_parent);
    virtual ~PackagesColumn() override = default;

    virtual void fill();
    virtual void clear();

    const std::deque<Package*>& getCheckedPackagesList() const;
    QStringList getCheckedPackagesStringList();
    uint getAurPackagesCount() const;

public Q_SLOTS:
    virtual void update(int exit_code,
                        QProcess::ExitStatus exit_status,
                        const QString& warning_title,
                        const QString& action_verb);

    virtual void sort(bool is_sorted);
    virtual void countCheckedPackages(QListWidgetItem* item);

signals:
   void checkedPackagesCounterChanged(bool has_checked_buttons);

protected:
    void addCheckedPackage(Package* package);
    void removeUncheckedPackage(Package* package);
    uint getWaitTime();

    int checked_packages;
    uint aur_checked_packages;
    QListWidget* list_widget;
    QLineEdit* search_lineedit;
    QScopedPointer<Sorter> packages_sorter;
    QWidget* parent;
    std::deque<Package*> checked_packages_list;
    static QWaitCondition condition;
    static bool is_condition_needed;
};

