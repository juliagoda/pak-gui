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

#include "package.h"

#include <QList>
#include <QListWidgetItem>
#include <QMutex>
#include <QCheckBox>

class Sorter : public QObject
{
    Q_OBJECT

public:
    Sorter(QListWidget* list_widgets,
           QCheckBox* new_reverse_sort_checkbox);
    ~Sorter() override;

    void resetOriginalList();
    bool isOriginalListEmpty() const;
    const QList<QListWidgetItem*>& listWidget() { return untouched_list_widget; }

    template <typename T>
    void sortPackagesByText(const QString& text, T emptyPackage);


public Q_SLOTS:
    void sortReverse();
    void setCheckStateForUnsortedList(QListWidgetItem* item);

private:
    void clear();
    void showInfo();
    void showInfoSortReverse(const QString& first_package_name,
                             const QString& second_package_name);

    template <typename T>
    void fillUntouchedList();

    template <typename T>
    void sortPackages(const QString& text, T emptyPackage);

    QListWidget* list_widget;
    QCheckBox* reverse_sort_checkbox;
    QList<QListWidgetItem*> untouched_list_widget;
    QMutex mutex;
};

