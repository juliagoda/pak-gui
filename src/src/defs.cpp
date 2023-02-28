#include "defs.h"


int Constants::packageQiNameLine()
{
    return 0;
}


int Constants::packageQiVersionLine()
{
    return 1;
}


int Constants::packageSiRepoName()
{
    return 0;
}


int Constants::packageSiNameLine()
{
    return 1;
}


int Constants::packageSiVersionLine()
{
    return 2;
}


QString Constants::pacmanExecFile()
{
    return "pacman";
}


QString Constants::pacmanContribExecFile()
{
    return "checkupdates";
}


QString Constants::kdesuExecFile()
{
    return "kdesu";
}


QString Constants::ksshAskPassExecFile()
{
    return "ksshaskpass";
}


QString Constants::pakExecFile()
{
    return "pak";
}


QString Constants::aspExecFile()
{
    return "asp";
}


QString Constants::gitExecFile()
{
    return "git";
}


QString Constants::reflectorExecFile()
{
    return "reflector";
}


QString Constants::auracleGitExecFile()
{
    return "auracle-git";
}


QString Constants::askPassCommand()
{
    return "export SUDO_ASKPASS=/usr/bin/ksshaskpass && sudo --askpass true";
}


QMap<Process::Task, Logger::WriteOperations> Constants::taskToWriteOperationMap()
{
    return {{Process::Task::Clean, Logger::WriteOperations::Clean},
           {Process::Task::MirrorsUpdate, Logger::WriteOperations::MirrorsUpdate},
           {Process::Task::UpdateAll, Logger::WriteOperations::UpdateAll},
           {Process::Task::PrintVCSPackages, Logger::WriteOperations::PrintVCSPackages},
           {Process::Task::UpdateInstalledPackages, Logger::WriteOperations::UpdateInstalled},
           {Process::Task::Uninstall, Logger::WriteOperations::Remove},
           {Process::Task::Install, Logger::WriteOperations::Install},
           {Process::Task::Update, Logger::WriteOperations::Update}};
}
