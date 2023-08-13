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

#include <algorithm>
#include <iterator>


QMutex Sorter::mutex;

Sorter::Sorter(QListWidget* list_widgets,
               QCheckBox* new_reverse_sort_checkbox) :
    list_widget(list_widgets),
    reverse_sort_checkbox(new_reverse_sort_checkbox),
    untouched_list_widget()
{
   // ...
}


void Sorter::sortReverse()
{
    mutex.lock();
    auto widgets_list = list_widget->findItems("*", Qt::MatchWildcard);

    clear();

    QList<QListWidgetItem*>::reverse_iterator widgets_it;
    for (widgets_it = widgets_list.rbegin(); widgets_it != widgets_list.rend(); widgets_it++)
    {
        list_widget->addItem(*widgets_it);
    }

    if (!widgets_list.empty())
        showInfoSortReverse(widgets_list.first()->text(), widgets_list.last()->text());
    mutex.unlock();
}


template<typename T>
void Sorter::sortPackagesByText(const QString &text, T emptyPackage)
{
    if (untouched_list_widget.empty())
        fillUntouchedList<T>();

    clear();
    if (sortPackagesAsReversed<T>(text, emptyPackage))
        return;

    sortPackages<T>(text, emptyPackage);
    showInfo();
}


template<typename T>
bool Sorter::sortPackagesAsReversed(const QString& text, T emptyPackage)
{
    Q_UNUSED(emptyPackage) // we have errors without T as argument
    QList<QListWidgetItem*>::reverse_iterator widgets_reversed_it;

    if (reverse_sort_checkbox->checkState() == Qt::Checked)
    {
        for (widgets_reversed_it = untouched_list_widget.rbegin(); widgets_reversed_it != untouched_list_widget.rend(); widgets_reversed_it++)
        {
            if (!(*widgets_reversed_it)->text().startsWith(text))
                continue;

            T* item = dynamic_cast<T*>(*widgets_reversed_it);
            list_widget->addItem(new T(*item));
        }

        showInfo();
        return true;
    }

    return false;
}


template<typename T>
void Sorter::sortPackages(const QString& text, T emptyPackage)
{
    Q_UNUSED(emptyPackage) // we have errors without T as argument
    QList<QListWidgetItem*>::iterator widgets_it;
    for (widgets_it = untouched_list_widget.begin(); widgets_it != untouched_list_widget.end(); widgets_it++)
    {
        if (!(*widgets_it)->text().startsWith(text))
            continue;

        T* item = dynamic_cast<T*>(*widgets_it);
        list_widget->addItem(new T(*item));
    }
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
                   [=](QListWidgetItem* item) mutable { return new T(*dynamic_cast<T*>(item)); });
}


void Sorter::clear()
{
    while (list_widget->count() > 0)
    {
        if (list_widget->item(0))
            list_widget->takeItem(0);
    }
}


void Sorter::resetOriginalList()
{
    if (untouched_list_widget.count() == 0)
        return;

    while (!untouched_list_widget.empty())
        delete untouched_list_widget.takeAt(0);
}


// forward declarations

template void Sorter::sortPackagesByText(const QString& text, CheckPackage);
template void Sorter::sortPackagesByText(const QString& text, SiPackage);
template void Sorter::sortPackagesByText(const QString& text, QiPackage);

template bool Sorter::sortPackagesAsReversed(const QString& text, CheckPackage);
template bool Sorter::sortPackagesAsReversed(const QString& text, SiPackage);
template bool Sorter::sortPackagesAsReversed(const QString& text, QiPackage);

template void Sorter::sortPackages(const QString& text, CheckPackage);
template void Sorter::sortPackages(const QString& text, SiPackage);
template void Sorter::sortPackages(const QString& text, QiPackage);




