#pragma once

#include "pakGuiSettings.h"
#include "process.h"
#include "logger.h"

#include <QString>
#include <QDir>
#include <QMap>

constexpr int PACKAGE_QI_NAME_LINE = 0;
constexpr int PACKAGE_QI_VERSION_LINE = 1;

constexpr int PACKAGE_SI_REPO_NAME = 0;
constexpr int PACKAGE_SI_NAME_LINE = 1;
constexpr int PACKAGE_SI_VERSION_LINE = 2;

const QString PACMAN_EXEC_FILE = "pacman";
const QString PACMAN_CONTRIB_EXEC_FILE = "checkupdates";
const QString KDESU_EXEC_FILE = "kdesu";
const QString PAK_EXEC_FILE = "pak";
const QString ASP_EXEC_FILE = "asp";
const QString GIT_EXEC_FILE = "git";
const QString REFLECTOR_EXEC_FILE = "reflector";
const QString AURACLE_EXEC_FILE = "auracle-git";

const QMap<Process::Task, Logger::WriteOperations> task_to_write_operation_map{
    {Process::Task::Clean, Logger::WriteOperations::Clean},
    {Process::Task::MirrorsUpdate, Logger::WriteOperations::MirrorsUpdate},
    {Process::Task::UpdateAll, Logger::WriteOperations::UpdateAll},
    {Process::Task::PrintVCSPackages, Logger::WriteOperations::PrintVCSPackages},
    {Process::Task::UpdateInstalledPackages, Logger::WriteOperations::UpdateInstalled},
    {Process::Task::Uninstall, Logger::WriteOperations::Remove},
    {Process::Task::Install, Logger::WriteOperations::Install},
    {Process::Task::Update, Logger::WriteOperations::Update}
};

struct Converter
{
    static QString toAbsolutePath(const QString& new_path)
    {
        QString path = new_path;
        if (path.startsWith("~/"))
            return path.remove(0, 1).prepend(QDir().homePath());

        return path;
    }

    static QString fullConfigPath()
    {
        return toAbsolutePath(pakGuiSettings::logs_filepath()).append("/" + pakGuiSettings::logs_filename());
    }

    static int minutesToMiliseconds(int minutes)
    {
        return minutes * 60000;
    }

    static int bytesToMegabytes(int bytes)
    {
        return bytes / 1000000;
    }

    static int megabytesToBytes(int megabytes)
    {
        return megabytes * 1000000;
    }
};
