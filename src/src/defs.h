#pragma once

#include "process.h"
#include "logger.h"

#include <QString>
#include <QMap>


class Constants
{
public:
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
};
