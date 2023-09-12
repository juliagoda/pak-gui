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

#include "commandparser.h"
#include "src/outputfilter.h"

#include <QProcess>
#include <QString>
#include <QStringList>
#include <QRegularExpression>


class SearchAllCommandParser : public CommandParser
{
    Q_OBJECT

public:
    SearchAllCommandParser(const QString& new_package_name);
    ~SearchAllCommandParser() override = default;

    virtual QStringList retrieveInfo() override;
    void stop();

protected Q_SLOTS:
    void finishProcess(int exit_code, QProcess::ExitStatus exit_status);
    void showError(const QString& errorString);

signals:
    void searchEnded(const QStringList& results);

protected:
    void processReadLine(const QString& line, QString& current_source_line);

private:
    QScopedPointer<QProcess> pak_search{nullptr};
    QString package_name;
    QStringList packages_lines;

    QScopedPointer<OutputFilter> output_filter;
};

