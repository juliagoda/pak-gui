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

#include "installcommandparser.h"
#include "logger.h"

#include <QSharedPointer>


InstallCommandParser::InstallCommandParser() :
    package_name(""),
    current_task(),
    sourceToTaskMap()
{
    init();
}


void InstallCommandParser::init()
{
    sourceToTaskMap.insert(QString("AUR"), Process::Task::InstallAfterSearchAUR);
    sourceToTaskMap.insert(QString("POLAUR"), Process::Task::InstallAfterSearchPOLAUR);
    sourceToTaskMap.insert(QString("Repositories"), Process::Task::InstallAfterSearchRepo);
}


void InstallCommandParser::updatePackageName(const QString& new_package_name)
{
    package_name = new_package_name;
}


void InstallCommandParser::updateTask(const QString& source_name)
{
    if (!sourceToTaskMap.contains(source_name))
    {
        current_task = Process::Task::InstallAfterSearchRepo;
        return;
    }

    current_task = sourceToTaskMap.value(source_name);
}


QString InstallCommandParser::getPackageName()
{
    return package_name;
}


QStringList InstallCommandParser::retrieveInfo()
{
    return QStringList();
}


void InstallCommandParser::start(QSharedPointer<Process>& process,
                                 uint packages_to_update)
{
    pak_install = process;
    process->setPackagesToUpdate(packages_to_update);

    if (process->preparedBeforeRun(current_task, QStringList() << package_name))
        process->run(current_task, QStringList() << package_name);
}


void InstallCommandParser::stop()
{
    if (!pak_install.isNull())
    {
        Logger::logger()->logInfo(QStringLiteral("Stop of package installation"));
        pak_install->stop();
        emit ended();
    }
}
