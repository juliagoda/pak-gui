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
    QCOMPARE(Constants::auracleGitExecFile(), QString("auracle-git"));
}


void TestDefs::ksshAskPassCommandIsCorrect()
{
    QCOMPARE(Constants::askPassCommand(), QString("export SUDO_ASKPASS=/usr/bin/ksshaskpass && sudo --askpass true"));
}


void TestDefs::taskToWriteOperationMapHasCorrectValues()
{
    QMap<Process::Task, Logger::WriteOperations> map{{{Process::Task::Clean, Logger::WriteOperations::Clean},
            {Process::Task::MirrorsUpdate, Logger::WriteOperations::MirrorsUpdate},
            {Process::Task::UpdateAll, Logger::WriteOperations::UpdateAll},
            {Process::Task::PrintVCSPackages, Logger::WriteOperations::PrintVCSPackages},
            {Process::Task::UpdateInstalledPackages, Logger::WriteOperations::UpdateInstalled},
            {Process::Task::Uninstall, Logger::WriteOperations::Remove},
            {Process::Task::Install, Logger::WriteOperations::Install},
            {Process::Task::Update, Logger::WriteOperations::Update}}};

    QCOMPARE(Constants::taskToWriteOperationMap(), map);
}
