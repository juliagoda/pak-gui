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
#include <QPair>

#include <unordered_map>


class Constants
{
public:
    Constants();
    void init();

    using Yes = QString;
    using No = QString;

    static constexpr int packageQiNameLine();
    static constexpr int packageQiVersionLine();
    static constexpr int packageSiRepoName();
    static constexpr int packageSiNameLine();
    static constexpr int packageSiVersionLine();

    static const QString pacmanExecFile();
    static const QString pacmanContribExecFile();
    static const QString kdesuExecFile();
    static const QString ksshAskPassExecFile();
    static const QString pakExecFile();
    static const QString aspExecFile();
    static const QString gitExecFile();
    static const QString reflectorExecFile();
    static const QString auracleGit();
    static const QString askPassCommand();

    static Logger::WriteOperations taskToWriteOperation(Process::Task task) const;
    static QPair<Constants::Yes, Constants::No> langNamesToYesNo(QLocale::Language language) const;

private:
    static QMap<Process::Task, Logger::WriteOperations> task_to_write_operation_map;
    static std::unordered_map<QLocale::Language, QPair<Yes, No>> lang_names_to_yes_no_map;
};
