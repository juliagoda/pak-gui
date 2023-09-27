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
   QCOMPARE(constants.packageQiNameLine(), 0);
}


void TestDefs::packageQiVersionLineIsEqualToOne()
{
   QCOMPARE(constants.packageQiVersionLine(), 1);
}


void TestDefs::packageSiRepoNameIsEqualToZero()
{
   QCOMPARE(constants.packageSiRepoName(), 0);
}


void TestDefs::packageSiNameLineIsEqualToOne()
{
   QCOMPARE(constants.packageSiNameLine(), 1);
}


void TestDefs::packageSiVersionLineIsEqualToTwo()
{
   QCOMPARE(constants.packageSiVersionLine(), 2);
}


void TestDefs::execFilesHaveCorrectNames()
{
    QCOMPARE(constants.pacmanExecFile(), QString("pacman"));
    QCOMPARE(constants.pacmanContribExecFile(), QString("checkupdates"));
    QCOMPARE(constants.kdesuExecFile(), QString("kdesu"));
    QCOMPARE(constants.ksshAskPassExecFile(), QString("ksshaskpass"));
    QCOMPARE(constants.pakExecFile(), QString("pak"));
    QCOMPARE(constants.pkgctlExecFile(), QString("pkgctl"));
    QCOMPARE(constants.gitExecFile(), QString("git"));
    QCOMPARE(constants.reflectorExecFile(), QString("reflector"));
    QCOMPARE(constants.auracleGit(), QString("auracle"));
}


void TestDefs::ksshAskPassCommandIsCorrect()
{
    QCOMPARE(constants.askPassCommand(), QString("export SUDO_ASKPASS=/usr/bin/ksshaskpass && sudo --askpass true"));
}


void TestDefs::taskToWriteOperationMapHasCorrectValues()
{
    Constants constants;
    constants.init();
    QCOMPARE(constants.taskToWriteOperation(Process::Task::MirrorsUpdate), Logger::WriteOperations::MirrorsUpdate);
    QCOMPARE(constants.taskToWriteOperation(Process::Task::UpdateAll), Logger::WriteOperations::UpdateAll);
    QCOMPARE(constants.taskToWriteOperation(Process::Task::PrintVCSPackages), Logger::WriteOperations::PrintVCSPackages);
    QCOMPARE(constants.taskToWriteOperation(Process::Task::UpdateInstalledPackages), Logger::WriteOperations::UpdateInstalled);
    QCOMPARE(constants.taskToWriteOperation(Process::Task::Uninstall), Logger::WriteOperations::Remove);
    QCOMPARE(constants.taskToWriteOperation(Process::Task::Install), Logger::WriteOperations::Install);
    QCOMPARE(constants.taskToWriteOperation(Process::Task::Update), Logger::WriteOperations::Update);
    QCOMPARE(constants.taskToWriteOperation(Process::Task::Clean), Logger::WriteOperations::Clean);
}
