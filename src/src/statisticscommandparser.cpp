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

#include "statisticscommandparser.h"

#include "logger.h"
#include "outputfilter.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>


QStringList StatisticsCommandParser::retrieveInfo()
{
    QString output = generateResult();

    Logger::logger()->writeToFile(output, Logger::WriteOperations::ShowStatistics);

    QStringList output_list = output.split(QRegExp("[\r\n]"), Qt::SkipEmptyParts);
    QStringListIterator it(output_list);
    QStringList result = QStringList();

    while (it.hasNext())
    {
        QString line{it.next().toUtf8()};
        QString filtered_line = outputfilter->filteredOutput(line);
        QRegExp action_regex{"^[\\w+\\s+]+:\\s+\\d+"};
        if (action_regex.exactMatch(filtered_line))
           result.append(filtered_line);
    }

    return result;
}


QString StatisticsCommandParser::generateResult()
{
    QScopedPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -L");
    pacman_qi->waitForStarted(-1);
    pacman_qi->waitForFinished(-1);
    auto result = QString::fromUtf8(pacman_qi->readAll());
    clearAfterExecution(pacman_qi);
    return result;
}


QMap<QString, uint> StatisticsCommandParser::convertToMap(const QStringList& retrievedInfos)
{
    QMap<QString, uint> retrievedInfoMap;
    std::for_each(retrievedInfos.begin(), retrievedInfos.end(), [&retrievedInfoMap](const QString& retrievedInfo)
    {
       uint separatorIndex = retrievedInfo.indexOf(":");
       retrievedInfoMap.insert(retrievedInfo.mid(0, separatorIndex).toUtf8(), retrievedInfo.midRef(separatorIndex + 1).toUInt());
    });

    return retrievedInfoMap;
}
