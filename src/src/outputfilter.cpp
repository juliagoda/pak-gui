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

#include "outputfilter.h"

#include <QFuture>
#include <QRegExp>
#include <QtConcurrent/QtConcurrent>


QList<QRegExp> OutputFilter::filtersList = initializeList();


QString OutputFilter::filteredOutput(QString& text_output)
{
    QList<QRegExp>::const_iterator filters_it;
    for (filters_it = filtersList.cbegin(); filters_it != filtersList.cend(); filters_it++)
        text_output.remove(*filters_it);

    return text_output;
}


QStringList OutputFilter::filteredOutputFromInstalledPackages(const QStringList& text_output)
{
    QStringList output_list;
    QStringList::const_iterator list_it;
    static QRegularExpression tag{"\\[.*\\]"};
    std::accumulate(text_output.begin(), text_output.end(), &output_list, [&](QStringList* list, const QString& elem)
    {
        QString output = elem;
        if (output.count(tag) == 1)
            output_list.append(output.trimmed());

        return list;
    });

    return output_list;
}


QString OutputFilter::getSourceFromDoubleColon(QString& output_line)
{
    return output_line.remove(QString("::")).trimmed();
}


QString OutputFilter::getSourceFromSearchLine(QString& output_line)
{
    static QRegularExpression regex(".*\\[(.*)\\].*");
    return regex.match(output_line).captured(1);
}


QString OutputFilter::getPackageFromSearchLine(QString& output_line)
{
    static QRegularExpression regex("^(\\S*)\\s*\\S*");
    return regex.match(output_line).captured(1);
}


void OutputFilter::addToList(QStringList& lines_list, const QString& line)
{
    lines_list.append(line);
}


QStringList OutputFilter::filteredLines(QStringList& output_lines, std::function<bool (const QString&)> conditional)
{
    QFuture<QStringList> filtered_strings = QtConcurrent::filteredReduced(output_lines, conditional, addToList);
    return filtered_strings.result();
}


QList<QRegExp> OutputFilter::initializeList()
{
    constexpr int size = 9;
    QList<QRegExp> filters;
    filters.reserve(size);
    filters.append(QRegExp("\u001B"));
    filters.append(QRegExp("\\[[0-9]{2}m"));
    filters.append(QRegExp("\\[0m"));
    filters.append(QRegExp("\\[1;[0-9]{2}m"));
    filters.append(QRegExp(""));
    filters.append(QRegExp("\\[?25l"));
    filters.append(QRegExp("\\[\\?"));
    filters.append(QRegExp("\\[[0-9]{1}F "));
    filters.append(QRegExp("\\[1E"));

    return filters;
}


bool OutputFilter::startsFromNumber(const QString& output_line)
{
    return output_line.contains(QRegExp("^\\s*[0-9]+\\.?\\s+"));
}


bool OutputFilter::startsFromDoubleColon(const QString& output_line)
{
    return output_line.startsWith(QString(":: "));
}


bool OutputFilter::isPackageLine(const QString &output_line)
{
    return output_line.contains(QRegExp("^.*/\\S+\\s+\\d+\\.\\d+.\\d+.*"));
}


bool OutputFilter::isCheckWarningLine(const QString& output_line)
{
    return output_line.count(':') >= 2 && output_line.contains(QRegExp("\\(.*=>.*\\)"));
}


