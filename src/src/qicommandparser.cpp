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

    if (output.isEmpty())
        return QStringList();

    auto list = output.split(QRegularExpression("\n\n"));
    output.clear();
    if (list.last().trimmed().isEmpty())
        list.pop_back();

    return list;
}


QString QiCommandParser::generateResult()
{
    QProcess pacman_qi;
    emit processStarted(&pacman_qi);
    pacman_qi.setProcessChannelMode(QProcess::MergedChannels);
    pacman_qi.start("/bin/bash", QStringList() << "-c" << "pak -Qi");
    pacman_qi.waitForStarted(-1);
    pacman_qi.waitForFinished(-1);
    pacman_qi.closeReadChannel(QProcess::StandardOutput);
    pacman_qi.closeReadChannel(QProcess::StandardError);
    pacman_qi.closeWriteChannel();
    auto result = pacman_qi.readAllStandardOutput();
    pacman_qi.close();
    pacman_qi.kill();
    emit processEnded();
    return result;
}
