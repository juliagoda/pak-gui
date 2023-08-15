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

#include "sicommandparser.h"

#include "logger.h"

#include <QString>
#include <QRegularExpression>


QStringList SiCommandParser::retrieveInfo()
{
    QString output = generateResult();

    Logger::logger()->writeToFile(output, Logger::WriteOperations::CheckAvailable);

    static QRegularExpression new_lines_expression("\n\n");
    auto list = output.split(new_lines_expression);
    if (list.last().trimmed().isEmpty())
        list.pop_back();

    return list;
}


QString SiCommandParser::generateResult()
{
    killProcess(pacman_si);
    pacman_si.reset(new QProcess(this), &QObject::deleteLater);
    pacman_si->setProcessChannelMode(QProcess::MergedChannels);
    pacman_si.data()->start("/bin/bash", QStringList() << "-c" << "pak -Si");
    pacman_si.data()->waitForStarted();
    pacman_si->waitForFinished();
    return pacman_si->readAllStandardOutput();
}
