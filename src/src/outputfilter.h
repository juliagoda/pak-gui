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

#pragma once

#include <QList>
#include <QRegExp>
#include <QStringList>
#include <functional>


class OutputFilter
{
public:
    explicit OutputFilter() = default;
    virtual ~OutputFilter() = default;

    QString filteredOutput(QString& text_output);
    QStringList filteredOutputFromInstalledPackages(const QStringList& text_output);
    QString getSourceFromDoubleColon(QString& output_line);
    QString getSourceFromSearchLine(QString& output_line);
    QString getPackageFromSearchLine(QString& output_line);
    QStringList filteredLines(QStringList& output_lines, std::function<bool(const QString&)> conditional);
    static bool startsFromNumber(const QString& output_line);
    bool startsFromDoubleColon(const QString& output_line);
    bool isPackageLine(const QString& output_line);
    bool isCheckWarningLine(const QString& output_line);

private:
    static QList<QRegExp> initializeList();
    static void addToList(QStringList& lines_list, const QString& line);

    static QList<QRegExp> filtersList;
};

