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

#pragma once

#include <QString>
#include <QStringList>
#include <QMap>

template<typename T>
class Algorithms
{
public:
    explicit Algorithms(const QString& separator,
                        const QList<T>& list,
                        const QHash<int, T>& map);

    QStringList createSplittedList(const QString& text);

private:
    void createListOfLines(QStringList& selected_infos,
                           const QString& text);


    bool foundIndexOdSeparator(const QString& line,
                               int& index_of_separator,
                               int& i,
                               QStringList& selected_infos,
                               int& last_index);

    int getFirstIndexAfterSeparator(T tooltip_part,
                                    QStringList& selected_infos,
                                    const QString& line);

    const QString separator;
    const QList<T> list;
    const QHash<int, T> map;
};

