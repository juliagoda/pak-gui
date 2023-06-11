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

#include "searchallcommandparser.h"

#include "outputfilter.h"
#include "logger.h"

#include <QPointer>


SearchAllCommandParser::SearchAllCommandParser(const QString& new_package_name) :
    package_name(new_package_name),
    packages_lines()
{
   // ...
}


QStringList SearchAllCommandParser::retrieveInfo()
{
    packages_lines.clear();
    QString current_source_line = QString();
    QPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->setProcessChannelMode(QProcess::MergedChannels);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -SS " + package_name);
    pacman_qi->waitForStarted();

    Logger::logger()->logInfo(QStringLiteral("Trying search package: %1 everywhere").arg(package_name));
    Logger::logger()->writeSectionToFile(Logger::WriteOperations::SearchAll);
    QObject::connect(pacman_qi, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &SearchAllCommandParser::finishProcess);
    QObject::connect(pacman_qi, &QProcess::errorOccurred, [&pacman_qi, this](QProcess::ProcessError /*error*/) { showError(pacman_qi->errorString()); });

    QObject::connect(pacman_qi, &QProcess::readyReadStandardOutput, [pacman_qi, current_source_line, this]() mutable
    {
        while (pacman_qi.data()->canReadLine())
        {
            QString line = pacman_qi.data()->readLine();
            processReadLine(line, current_source_line);
        }
    });

    return QStringList();
}


void SearchAllCommandParser::finishProcess(int /*exit_code*/, QProcess::ExitStatus /*exit_status*/)
{
    Logger::logger()->logInfo(QStringLiteral("Found %1 sources during package search").arg(packages_lines.count()));
    emit searchEnded(packages_lines);
}


void SearchAllCommandParser::showError(const QString& errorString)
{
    Logger::logger()->logFatal(QStringLiteral("Error during search: %1").arg(errorString));
}


void SearchAllCommandParser::processReadLine(QString& line, QString& current_source_line)
{
    auto filtered_line = OutputFilter::filteredOutput(line).remove("\n");
    Logger::logger()->writeLineToFile(filtered_line);

    if (OutputFilter::startsFromDoubleColon(filtered_line))
        current_source_line = OutputFilter::getSourceFromDoubleColon(filtered_line);

    if (OutputFilter::isPackageLine(filtered_line))
    {
        QString appendedSourceToLine(" [" + current_source_line + "]\n");
        packages_lines.append(filtered_line.append(appendedSourceToLine));
    }
}
