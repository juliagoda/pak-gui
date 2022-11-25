#pragma once

#include "pakGuiSettings.h"
#include <QString>
#include <QDir>

constexpr int PACKAGE_QI_NAME_LINE = 0;
constexpr int PACKAGE_QI_VERSION_LINE = 1;
constexpr int PACKAGE_QI_DESCRIPTION_LINE = 2;
constexpr int PACKAGE_QI_DEPENDENCIES_LINE = 8;

constexpr int PACKAGE_SI_NAME_LINE = 1;
constexpr int PACKAGE_SI_VERSION_LINE = 2;
constexpr int PACKAGE_SI_DESCRIPTION_LINE = 3;
constexpr int PACKAGE_SI_DEPENDENCIES_LINE = 9;

const QString PACMAN_EXEC_FILE = "pacman";
const QString PACMAN_CONTRIB_EXEC_FILE = "checkupdates";
const QString KDESU_EXEC_FILE = "kdesu";
const QString PAK_EXEC_FILE = "pak";
const QString ASP_EXEC_FILE = "asp";
const QString GIT_EXEC_FILE = "git";
const QString REFLECTOR_EXEC_FILE = "reflector";
const QString AURACLE_EXEC_FILE = "auracle-git";

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
};
