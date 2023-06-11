// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of tests for CachyOS package manager (based on "pak" application).
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

#include "defstest.h"

#include "defs.h"
#include "logger.h"


TestDefs::TestDefs(QObject* parent) :
    QObject{parent}
{
   // ...
}

void TestDefs::packageQiNameLineIsEqualToZero()
{
   QCOMPARE(Constants::packageQiNameLine(), 0);
}


void TestDefs::packageQiVersionLineIsEqualToOne()
{
   QCOMPARE(Constants::packageQiVersionLine(), 1);
}


void TestDefs::packageSiRepoNameIsEqualToZero()
{
   QCOMPARE(Constants::packageSiRepoName(), 0);
}


void TestDefs::packageSiNameLineIsEqualToOne()
{
   QCOMPARE(Constants::packageSiNameLine(), 1);
}


void TestDefs::packageSiVersionLineIsEqualToTwo()
{
   QCOMPARE(Constants::packageSiVersionLine(), 2);
}


void TestDefs::execFilesHaveCorrectNames()
{
    QCOMPARE(Constants::pacmanExecFile(), QString("pacman"));
    QCOMPARE(Constants::pacmanContribExecFile(), QString("checkupdates"));
    QCOMPARE(Constants::kdesuExecFile(), QString("kdesu"));
    QCOMPARE(Constants::ksshAskPassExecFile(), QString("ksshaskpass"));
    QCOMPARE(Constants::pakExecFile(), QString("pak"));
    QCOMPARE(Constants::aspExecFile(), QString("asp"));
    QCOMPARE(Constants::gitExecFile(), QString("git"));
    QCOMPARE(Constants::reflectorExecFile(), QString("reflector"));
    QCOMPARE(Constants::auracleGit(), QString("auracle"));
}


void TestDefs::ksshAskPassCommandIsCorrect()
{
    QCOMPARE(Constants::askPassCommand(), QString("export SUDO_ASKPASS=/usr/bin/ksshaskpass && sudo --askpass true"));
}


void TestDefs::taskToWriteOperationMapHasCorrectValues()
{
    Constants constants;
    constants.init();
    QCOMPARE(Constants::taskToWriteOperation(Process::Task::MirrorsUpdate), Logger::WriteOperations::MirrorsUpdate);
    QCOMPARE(Constants::taskToWriteOperation(Process::Task::UpdateAll), Logger::WriteOperations::UpdateAll);
    QCOMPARE(Constants::taskToWriteOperation(Process::Task::PrintVCSPackages), Logger::WriteOperations::PrintVCSPackages);
    QCOMPARE(Constants::taskToWriteOperation(Process::Task::UpdateInstalledPackages), Logger::WriteOperations::UpdateInstalled);
    QCOMPARE(Constants::taskToWriteOperation(Process::Task::Uninstall), Logger::WriteOperations::Remove);
    QCOMPARE(Constants::taskToWriteOperation(Process::Task::Install), Logger::WriteOperations::Install);
    QCOMPARE(Constants::taskToWriteOperation(Process::Task::Update), Logger::WriteOperations::Update);
    QCOMPARE(Constants::taskToWriteOperation(Process::Task::Clean), Logger::WriteOperations::Clean);
}
