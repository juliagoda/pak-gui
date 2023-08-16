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
    packages_lines(),
    output_filter{new OutputFilter}
{
   // ...
}


QStringList SearchAllCommandParser::retrieveInfo()
{
    packages_lines.clear();
    QString current_source_line = QString();
    pak_search.reset(new QProcess);
    pak_search->setProcessChannelMode(QProcess::MergedChannels);
    pak_search->start("/bin/bash", QStringList() << "-c" << "pak -SS " + package_name);
    pak_search->waitForStarted();

    Logger::logger()->logInfo(QStringLiteral("Trying search package: %1 everywhere").arg(package_name));
    Logger::logger()->writeSectionToFile(Logger::WriteOperations::SearchAll);
    QObject::connect(pak_search.get(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &SearchAllCommandParser::finishProcess);
    QObject::connect(pak_search.get(), &QProcess::errorOccurred, [this](QProcess::ProcessError /*error*/)
    {
        showError(pak_search->errorString());
        clearAfterExecution(pak_search);
    });

    QObject::connect(pak_search.get(), &QProcess::readyReadStandardOutput, [current_source_line, this]() mutable
    {
        while (pak_search.data()->canReadLine())
        {
            QString line = pak_search.data()->readLine();
            processReadLine(line, current_source_line);
        }
    });

    return QStringList();
}


void SearchAllCommandParser::finishProcess(int /*exit_code*/, QProcess::ExitStatus /*exit_status*/)
{
    Logger::logger()->logInfo(QStringLiteral("Found %1 sources during package search").arg(packages_lines.count()));
    emit searchEnded(packages_lines);
    clearAfterExecution(pak_search);
}


void SearchAllCommandParser::showError(const QString& errorString)
{
    Logger::logger()->logFatal(QStringLiteral("Error during search: %1").arg(errorString));
}


void SearchAllCommandParser::processReadLine(const QString& line, QString& current_source_line)
{
    auto filtered_line = output_filter->filteredOutput(line).remove("\n");
    Logger::logger()->writeLineToFile(filtered_line);

    if (output_filter->startsFromDoubleColon(filtered_line))
        current_source_line = output_filter->getSourceFromDoubleColon(filtered_line);

    if (output_filter->isPackageLine(filtered_line))
    {
        QString appendedSourceToLine(" [" + current_source_line + "]\n");
        packages_lines.append(filtered_line.append(appendedSourceToLine));
    }
}


void SearchAllCommandParser::stop()
{
    Logger::logger()->logInfo(QStringLiteral("Stop of package search"));
    clearAfterExecution(pak_search);
}
