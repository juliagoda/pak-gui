// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of package manager based on "pak" application.
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

#include "algorithms.h"

#include "package.h"


template class Algorithms<Package::TooltipLine>;


template<typename T>
Algorithms<T>::Algorithms(const QString& new_separator,
                          const QList<T>& new_list,
                          const QHash<int, T>& new_map) :
                          separator{new_separator}, list{new_list}, map{new_map}
{
    // ...
}


template<typename T>
QStringList Algorithms<T>::createSplittedList(const QString& text)
{
    QStringList selected_infos{};
    int selected_info_size = list.count();

    while (selected_info_size > 0)
    {
        selected_infos.append("");
        --selected_info_size;
    }

    Q_ASSERT(selected_infos.count() == list.count());

    if (text.isEmpty() || selected_infos.isEmpty())
        return QStringList();

    createListOfLines(selected_infos, text);
    return selected_infos;
}


template<typename T>
void Algorithms<T>::createListOfLines(QStringList& selected_infos,
                                      const QString& text)
{
    const auto& lines_list = text.split('\n');
    int i = 0;
    int last_index = -1;
    int index_of_separator = 0;

    std::for_each(lines_list.begin(), lines_list.end(), [&](const QString& line)
    {
        if (foundIndexOdSeparator(line, index_of_separator, i, selected_infos, last_index))
            return line;

        if (last_index < 0)
            return line;

        QString leading_whitespaces{};
        selected_infos[last_index] += "\n" + leading_whitespaces.fill(' ', index_of_separator) + line;
        return line;
    });
}


template<typename T>
bool Algorithms<T>::foundIndexOdSeparator(const QString& line,
                                          int& index_of_separator,
                                          int& i,
                                          QStringList& selected_infos,
                                          int& last_index)
{
    if (line.contains(separator))
    {
        i++;
        index_of_separator = line.indexOf(separator) + separator.count();
        auto tooltip_part = map.value(i);
        last_index = getFirstIndexAfterSeparator(tooltip_part, selected_infos, line);
        return true;
    }

    return false;
}


template<typename T>
int Algorithms<T>::getFirstIndexAfterSeparator(T tooltip_part,
                                               QStringList& selected_infos,
                                               const QString& line)
{
    if (list.contains(tooltip_part))
    {
        selected_infos[list.indexOf(tooltip_part)] = line;
        return list.indexOf(tooltip_part);
    }

    return -1;
}
