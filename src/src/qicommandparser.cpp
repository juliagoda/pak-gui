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

#include "qicommandparser.h"

#include "logger.h"

#include <QString>
#include <QRegularExpression>


QStringList QiCommandParser::retrieveInfo()
{
    QString output = generateResult();
    Logger::logger()->writeToFile(output, Logger::WriteOperations::CheckInstalled);

    static auto list = output.split(QRegularExpression("\n\n"));
    if (list.last().trimmed().isEmpty())
        list.pop_back();

    return list;
}


QString QiCommandParser::generateResult()
{
    killProcess(pacman_qi);
    pacman_qi.reset(new QProcess(this), &QObject::deleteLater);
    pacman_qi->setProcessChannelMode(QProcess::MergedChannels);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -Qi");
    pacman_qi->waitForStarted(-1);
    pacman_qi->waitForFinished(-1);
    return pacman_qi->readAllStandardOutput();
}
