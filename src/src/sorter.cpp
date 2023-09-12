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

#include "sorter.h"

#include "logger.h"
#include "settings.h"
#include "checkpackage.h"
#include "sipackage.h"
#include "qipackage.h"

#include <QFuture>
#include <QtConcurrent/QtConcurrent>

#include <execution>
#include <algorithm>
#include <iterator>


Sorter::Sorter(QListWidget* list_widgets,
               QCheckBox* new_reverse_sort_checkbox) :
    list_widget(list_widgets),
    reverse_sort_checkbox(new_reverse_sort_checkbox),
    untouched_list_widget()
{
    // ...
}


Sorter::~Sorter()
{
    resetOriginalList();
}


void Sorter::sortReverse()
{
    auto widgets_list = list_widget->findItems("*", Qt::MatchWildcard);

    clear();

    std::for_each(std::execution::par, widgets_list.rbegin(), widgets_list.rend(), [this](QListWidgetItem* item)
    {
        list_widget->addItem(item);
    });

    if (!widgets_list.empty())
        showInfoSortReverse(widgets_list.first()->text(), widgets_list.last()->text());
}


template<typename T>
void Sorter::sortPackagesByText(const QString& text, T emptyPackage)
{
    if (untouched_list_widget.empty())
        fillUntouchedList<T>();

    clear();
    sortPackages<T>(text, emptyPackage);
    showInfo();
}


template<typename T>
void Sorter::sortPackages(const QString& text, T emptyPackage)
{
    Q_UNUSED(emptyPackage) // we have errors without T as argument
    std::for_each(std::execution::par, untouched_list_widget.begin(), untouched_list_widget.end(), [&, this](QListWidgetItem* item)
        {
            if (!item->text().startsWith(text))
                return;

            list_widget->addItem(item);
        });
}


void Sorter::setCheckStateForUnsortedList(QListWidgetItem* item)
{
    if (!item)
        return;

    Package* package = dynamic_cast<Package*>(item);

    if (untouched_list_widget.empty() || package->getNo() > untouched_list_widget.count())
        return;

    untouched_list_widget.at(package->getNo() - 1)->setCheckState(item->checkState());
}


void Sorter::showInfo()
{
    if (!Settings::records()->showDebug())
        return;

    auto all_items = list_widget->findItems("*", Qt::MatchWildcard);
    Logger::logger()->logDebug(QStringLiteral("Count of sorted packages: %1").arg(all_items.count()));
}


void Sorter::showInfoSortReverse(const QString& first_package_name,
                                 const QString& second_package_name)
{
    if (!Settings::records()->showDebug())
        return;

    Logger::logger()->logDebug(QStringLiteral("Reverse sorting - now first package is \"%1\" and last one \"%2\"").arg(first_package_name, second_package_name));
}


template <typename T>
void Sorter::fillUntouchedList()
{
    auto widgets_list = list_widget->findItems("*", Qt::MatchWildcard);
    untouched_list_widget.reserve(widgets_list.count());
    std::transform(widgets_list.begin(), widgets_list.end(), std::back_inserter(untouched_list_widget),
                   [=](QListWidgetItem* item) mutable { return item; });
}


void Sorter::clear()
{
    while (list_widget->count() > 0)
    {
        if (list_widget->item(0))
            list_widget->takeItem(0);
    }

    list_widget->clear();
}


void Sorter::resetOriginalList()
{
    if (untouched_list_widget.count() == 0)
        return;

    untouched_list_widget.clear();
}


bool Sorter::isOriginalListEmpty() const
{
    return untouched_list_widget.empty();
}


// forward declarations

template void Sorter::sortPackagesByText(const QString& text, CheckPackage);
template void Sorter::sortPackagesByText(const QString& text, SiPackage);
template void Sorter::sortPackagesByText(const QString& text, QiPackage);

template void Sorter::sortPackages(const QString& text, CheckPackage);
template void Sorter::sortPackages(const QString& text, SiPackage);
template void Sorter::sortPackages(const QString& text, QiPackage);




