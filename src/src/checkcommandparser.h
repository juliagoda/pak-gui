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

#include "commandparser.h"
#include "package.h"
#include "src/outputfilter.h"

#include <QHash>
#include <QProcess>
#include <QScopedPointer>


class CheckCommandParser : public CommandParser
{
    Q_OBJECT

public:
    CheckCommandParser();
    virtual ~CheckCommandParser() override = default;

    QStringList retrieveInfo() override { return QStringList(); };
    QHash<QString, Package::Source> retrieveInfoMap();

protected:
    virtual QString generatePakCheckResults();

private:
    void processLines(QHash<QString, Package::Source>& system_packages,
                      QStringListIterator& iterator);
    void increaseDoubleColonCounter(const QString& filtered_line, uint& counter);
    void appendPackageLine(QHash<QString, Package::Source>& system_packages,
                           const QString& filtered_line, uint &counter);

    QHash<uint, Package::Source> line_to_source_map{};
    QScopedPointer<OutputFilter> output_filter{new OutputFilter};
};

