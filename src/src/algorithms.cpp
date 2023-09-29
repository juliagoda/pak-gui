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

#include "algorithms.h"

#include "package.h"

// TODOJG - reduce parameters list
template<typename T>
QStringList Algorithms::createSplittedList(const QString& text,
                                           const QString& separator,
                                           const QList<T>& list,
                                           const QHash<int, T>& map)
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

    createListOfLines<T>(selected_infos, text, separator, list, map);
    return selected_infos;
}

// TODOJG - reduce parameters list
template<typename T>
void Algorithms::createListOfLines(QStringList& selected_infos,
                                   const QString& text,
                                   const QString& separator,
                                   const QList<T>& list,
                                   const QHash<int, T>& map)
{
    const auto& lines_list = text.split('\n');
    int i = 0;
    int last_index = -1;
    int index_of_separator = 0;

    std::for_each(lines_list.begin(), lines_list.end(), [&](const QString& line)
    {
        if (foundIndexOdSeparator<T>(line, separator, index_of_separator, list, map, i, selected_infos, last_index))
            return line;

        if (last_index < 0)
            return line;

        QString leading_whitespaces{};
        selected_infos[last_index] += "\n" + leading_whitespaces.fill(' ', index_of_separator) + line;
        return line;
    });
}

// TODOJG - reduce parameters list
template<typename T>
bool Algorithms::foundIndexOdSeparator(const QString& line,
                                       const QString& separator,
                                       int& index_of_separator,
                                       const QList<T>& list,
                                       const QHash<int, T>& map,
                                       int& i,
                                       QStringList& selected_infos,
                                       int& last_index)
{
    if (line.contains(separator))
    {
        i++;
        index_of_separator = line.indexOf(separator) + separator.count();
        auto tooltip_part = map.value(i);
        last_index = getFirstIndexAfterSeparator<T>(list, tooltip_part, selected_infos, line);
        return true;
    }

    return false;
}

// TODOJG - reduce parameters list
template<typename T>
int Algorithms::getFirstIndexAfterSeparator(const QList<T>& list,
                                            T tooltip_part,
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


// forward declarations
// TODOJG - maybe better class template

template QStringList Algorithms::createSplittedList(const QString& text,
                                                    const QString& separator,
                                                    const QList<Package::TooltipLine>& list,
                                                    const QHash<int, Package::TooltipLine>& map);

template void Algorithms::createListOfLines(QStringList& selected_infos,
                                            const QString& text,
                                            const QString& separator,
                                            const QList<Package::TooltipLine>& list,
                                            const QHash<int, Package::TooltipLine>& map);

template bool Algorithms::foundIndexOdSeparator(const QString& line_it,
                                                const QString& separator,
                                                int& index_of_separator,
                                                const QList<Package::TooltipLine>& list,
                                                const QHash<int, Package::TooltipLine>& map,
                                                int& i,
                                                QStringList& selected_infos,
                                                int& last_index);

template int Algorithms::getFirstIndexAfterSeparator(const QList<Package::TooltipLine>& list,
                                                     Package::TooltipLine tooltip_part,
                                                     QStringList& selected_infos,
                                                     const QString& line);



