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

#include "process.h"
#include "logger.h"

#include <QString>
#include <QMap>
#include <QLocale>


class Constants
{
public:
    using Yes = QString;
    using No = QString;

    static int packageQiNameLine();
    static int packageQiVersionLine();
    static int packageSiRepoName();
    static int packageSiNameLine();
    static int packageSiVersionLine();

    static QString pacmanExecFile();
    static QString pacmanContribExecFile();
    static QString kdesuExecFile();
    static QString ksshAskPassExecFile();
    static QString pakExecFile();
    static QString aspExecFile();
    static QString gitExecFile();
    static QString reflectorExecFile();
    static QString auracleGit();

    static QString askPassCommand();
    static QMap<Process::Task, Logger::WriteOperations> taskToWriteOperationMap();
    static QHash<QLocale::Language, QPair<Yes, No>> langNamesToYesNoMap();
};
