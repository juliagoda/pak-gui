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

#include "emptycolumnfill.h"
#include "qipackage.h"
#include "sipackage.h"

#include <algorithm>


template class EmptyColumnFill<QiPackage>;
template class EmptyColumnFill<SiPackage>;


template<class T>
EmptyColumnFill<T>::EmptyColumnFill(const QStringList& new_pak_packages, QListWidget* new_list_widget) :
    pak_packages(new_pak_packages),
    list_widget(new_list_widget)
{
   // ...
}


template<class T>
void EmptyColumnFill<T>::fill()
{
    int i = 0;

    std::for_each(pak_packages.cbegin(), pak_packages.cend(), [this, &i](const QString& package)
    {
        T* package_item = new T(package, list_widget);
        package_item->setNo(i+1);
        Q_ASSERT(package_item != nullptr);
        Q_ASSERT(list_widget != nullptr);
        list_widget->addItem(package_item);
        i++;
    });
}
