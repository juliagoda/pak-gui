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

#include "existingfillcolumn.h"

#include "qipackage.h"
#include "sipackage.h"


template class ExistingFillColumn<QiPackage>;
template class ExistingFillColumn<SiPackage>;


template<class T>
ExistingFillColumn<T>::ExistingFillColumn(const QStringList& new_pak_packages, QListWidget* new_list_widget) :
    pak_packages(new_pak_packages),
    list_widget(new_list_widget)
{
  // ...
}


template<class T>
void ExistingFillColumn<T>::fill()
{
    for(int i = 0; i < list_widget->count(); i++)
    {
        T* package = dynamic_cast<T*>(list_widget->item(i));
        if (i+1 <= pak_packages.size() && !package->isEqualTo(pak_packages.at(i)))
        {
            package->prepareInformations(pak_packages.at(i));
        }

        if (i+1 > pak_packages.size())
            delete list_widget->takeItem(i);
    }
}
