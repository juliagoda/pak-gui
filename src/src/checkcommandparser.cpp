// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of package manager based on "pak" application.
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

#include "checkcommandparser.h"
#include "logger.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>


CheckCommandParser::CheckCommandParser()
{
     line_to_source_map.insert(1, Package::Source::Repo);
     line_to_source_map.insert(2, Package::Source::AUR);
     line_to_source_map.insert(3, Package::Source::POLAUR);
}


QHash<QString, Package::Source> CheckCommandParser::retrieveInfoMap()
{
    QString output{generatePakCheckResults()};

    decltype(retrieveInfoMap()) system_packages;

    if (output.isEmpty())
        return system_packages;

    const QStringList& output_list{output.split(QRegExp("[\r\n]"), Qt::SkipEmptyParts)};
    output.clear();
    QStringListIterator it{output_list};
    processLines(system_packages, it);

    return system_packages;
}


QString CheckCommandParser::generatePakCheckResults()
{
    QProcess pacman_check;
    emit processStarted(&pacman_check);
    pacman_check.setProcessChannelMode(QProcess::MergedChannels);
    pacman_check.start("/bin/bash", QStringList() << "-c" << "pak -C");
    pacman_check.waitForStarted(-1);
    pacman_check.waitForFinished(-1);
    pacman_check.closeReadChannel(QProcess::StandardOutput);
    pacman_check.closeReadChannel(QProcess::StandardError);
    pacman_check.closeWriteChannel();
    auto result = pacman_check.readAllStandardOutput();
    pacman_check.close();
    pacman_check.kill();
    emit processEnded();
    return result;
}


void CheckCommandParser::processLines(QHash<QString, Package::Source>& system_packages,
                                      QStringListIterator& iterator)
{
    uint double_colon_line_count{0};

    while (iterator.hasNext())
    {
        QString line{iterator.next()};
        const QString& filtered_line{output_filter->filteredOutput(line).simplified()};
        uint tempLineCount = double_colon_line_count;
        increaseDoubleColonCounter(filtered_line, double_colon_line_count);
        appendPackageLine(system_packages, filtered_line, double_colon_line_count);

        if (double_colon_line_count == 3 && tempLineCount == double_colon_line_count &&
            filtered_line.startsWith(":: "))
        {
            break;
        }
    }
}


void CheckCommandParser::increaseDoubleColonCounter(const QString& filtered_line, uint &counter)
{
    bool starts_from_double_colon{output_filter->startsFromDoubleColon(filtered_line)};

    if (starts_from_double_colon)
        counter++;
}


void CheckCommandParser::appendPackageLine(QHash<QString, Package::Source>& system_packages,
                                           const QString& filtered_line, uint& counter)
{
    if (filtered_line.contains("=>") && !output_filter->isCheckWarningLine(filtered_line))
        system_packages.insert(filtered_line, line_to_source_map.value(counter));
}
