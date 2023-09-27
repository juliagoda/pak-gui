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

#include "defs.h"

#include "process.h"


QMap<Process::Task, Logger::WriteOperations> Constants::task_to_write_operation_map;
std::unordered_map<QLocale::Language, QPair<QString, QString>> Constants::lang_names_to_yes_no_map;


Constants::Constants()
{
    // ...
}


void Constants::init()
{
    task_to_write_operation_map = {{Process::Task::Clean, Logger::WriteOperations::Clean},
            {Process::Task::MirrorsUpdate, Logger::WriteOperations::MirrorsUpdate},
            {Process::Task::UpdateAll, Logger::WriteOperations::UpdateAll},
            {Process::Task::PrintVCSPackages, Logger::WriteOperations::PrintVCSPackages},
            {Process::Task::UpdateInstalledPackages, Logger::WriteOperations::UpdateInstalled},
            {Process::Task::Uninstall, Logger::WriteOperations::Remove},
            {Process::Task::Install, Logger::WriteOperations::Install},
            {Process::Task::Update, Logger::WriteOperations::Update}};

    // TODOJG - maybe put it in external file
    lang_names_to_yes_no_map = {{QLocale::Polish, QPair{"T", "n"}},
                                {QLocale::English, QPair{"Y", "n"}},
                                {QLocale::German, QPair{"J", "n"}},
                                {QLocale::Hindi, QPair{"Y", "n"}},
                                {QLocale::Ukrainian, QPair{"Y", "n"}},
                                {QLocale::Greek, QPair{"Y", "n"}},
                                {QLocale::Russian, QPair{"Y", "n"}},
                                {QLocale::Bulgarian, QPair{"Y", "n"}},
                                {QLocale::Serbian, QPair{"Д", "н"}},
                                {QLocale::Japanese, QPair{"Y", "n"}},
                                {QLocale::French, QPair{"O", "n"}},
                                {QLocale::Korean, QPair{"Y", "n"}},
                                {QLocale::Spanish, QPair{"S", "n"}},
                                {QLocale::Bosnian, QPair{"Y", "n"}},
                                {QLocale::Hungarian, QPair{"I", "n"}},
                                {QLocale::Azerbaijani, QPair{"Y", "n"}},
                                {QLocale::Portuguese, QPair{"S", "n"}},
                                {QLocale::Italian, QPair{"S", "n"}},
                                {QLocale::Galician, QPair{"S", "n"}},
                                {QLocale::Turkish, QPair{"E", "h"}},
                                {QLocale::Lithuanian, QPair{"T", "n"}},
                                {QLocale::Czech, QPair{"A", "n"}},
                                {QLocale::Dutch, QPair{"J", "n"}},
                                {QLocale::Romanian, QPair{"D", "n"}},
                                {QLocale::Slovak, QPair{"A", "n"}},
                                {QLocale::Swedish, QPair{"J", "n"}},
                                {QLocale::Danish, QPair{"J", "n"}},
                                {QLocale::NorwegianBokmal, QPair{"J", "n"}},
                                {QLocale::Chinese, QPair{"Y", "n"}},
                                {QLocale::Basque, QPair{"B", "e"}},
                                {QLocale::Esperanto, QPair{"J", "n"}},
                                {QLocale::Finnish, QPair{"K", "e"}},
                                {QLocale::Indonesian, QPair{"Y", "n"}},
                                {QLocale::Slovenian, QPair{"D", "n"}}
                                };
}


const QString Constants::pacmanExecFile()
{
    return "pacman";
}


const QString Constants::pacmanContribExecFile()
{
    return "checkupdates";
}


const QString Constants::kdesuExecFile()
{
    return "kdesu";
}


const QString Constants::ksshAskPassExecFile()
{
    return "ksshaskpass";
}


const QString Constants::pakExecFile()
{
    return "pak";
}


const QString Constants::pkgctlExecFile()
{
    return "pkgctl";
}


const QString Constants::gitExecFile()
{
    return "git";
}


const QString Constants::reflectorExecFile()
{
    return "reflector";
}


const QString Constants::auracleGit()
{
    return "auracle";
}


const QString Constants::askPassCommand()
{
    return "export SUDO_ASKPASS=/usr/bin/ksshaskpass && sudo --askpass true";
}


Logger::WriteOperations Constants::taskToWriteOperation(Process::Task task)
{
    return task_to_write_operation_map.value(task);
}


QPair<Constants::Yes, Constants::No> Constants::langNamesToYesNo(QLocale::Language language)
{
    if (lang_names_to_yes_no_map.contains(language))
        return lang_names_to_yes_no_map.at(language);

    return QPair{"Y", "n"};
}

QHash<int, Package::TooltipLine> Constants::typePackageToTooltipLines(Package::Type package_type)
{
    switch(package_type)
    {
    case Package::Type::Si:
        return numberToTooltipLineSiPackage();
        break;

    case Package::Type::Qi:
        return numberToTooltipLineQiPackage();
        break;

    default:
        return numberToTooltipLineCheckPackage();
        break;
    }
}


QHash<int, Package::TooltipLine> Constants::numberToTooltipLineSiPackage()
{
    QHash<int, Package::TooltipLine> numberToTooltipLine;
    numberToTooltipLine.insert(2, Package::TooltipLine::Name);
    numberToTooltipLine.insert(3, Package::TooltipLine::Version);
    numberToTooltipLine.insert(4, Package::TooltipLine::Description);
    numberToTooltipLine.insert(5, Package::TooltipLine::Architecture);
    numberToTooltipLine.insert(6, Package::TooltipLine::URL);
    numberToTooltipLine.insert(7, Package::TooltipLine::Licenses);
    numberToTooltipLine.insert(8, Package::TooltipLine::Groups);
    numberToTooltipLine.insert(9, Package::TooltipLine::Provides);
    numberToTooltipLine.insert(10, Package::TooltipLine::DependsOn);
    numberToTooltipLine.insert(11, Package::TooltipLine::OptionalDeps);
    numberToTooltipLine.insert(12, Package::TooltipLine::ConflictsWith);
    numberToTooltipLine.insert(13, Package::TooltipLine::Replaces);
    numberToTooltipLine.insert(14, Package::TooltipLine::DownloadSize);
    numberToTooltipLine.insert(15, Package::TooltipLine::InstalledSize);
    numberToTooltipLine.insert(16, Package::TooltipLine::Packager);
    numberToTooltipLine.insert(17, Package::TooltipLine::BuildDate);
    numberToTooltipLine.insert(18, Package::TooltipLine::ValidatedBy);
    return numberToTooltipLine;
}


QHash<int, Package::TooltipLine> Constants::numberToTooltipLineQiPackage()
{
    QHash<int, Package::TooltipLine> numberToTooltipLine;
    numberToTooltipLine.insert(1, Package::TooltipLine::Name);
    numberToTooltipLine.insert(2, Package::TooltipLine::Version);
    numberToTooltipLine.insert(3, Package::TooltipLine::Description);
    numberToTooltipLine.insert(4, Package::TooltipLine::Architecture);
    numberToTooltipLine.insert(5, Package::TooltipLine::URL);
    numberToTooltipLine.insert(6, Package::TooltipLine::Licenses);
    numberToTooltipLine.insert(7, Package::TooltipLine::Groups);
    numberToTooltipLine.insert(8, Package::TooltipLine::Provides);
    numberToTooltipLine.insert(9, Package::TooltipLine::DependsOn);
    numberToTooltipLine.insert(10, Package::TooltipLine::OptionalDeps);
    numberToTooltipLine.insert(11, Package::TooltipLine::RequiredBy);
    numberToTooltipLine.insert(12, Package::TooltipLine::OptionalFor);
    numberToTooltipLine.insert(13, Package::TooltipLine::ConflictsWith);
    numberToTooltipLine.insert(14, Package::TooltipLine::Replaces);
    numberToTooltipLine.insert(15, Package::TooltipLine::InstalledSize);
    numberToTooltipLine.insert(16, Package::TooltipLine::Packager);
    numberToTooltipLine.insert(17, Package::TooltipLine::BuildDate);
    numberToTooltipLine.insert(18, Package::TooltipLine::InstallDate);
    numberToTooltipLine.insert(19, Package::TooltipLine::InstallReason);
    numberToTooltipLine.insert(20, Package::TooltipLine::InstallScript);
    numberToTooltipLine.insert(21, Package::TooltipLine::ValidatedBy);
    return numberToTooltipLine;
}


QHash<int, Package::TooltipLine> Constants::numberToTooltipLineCheckPackage()
{
    QHash<int, Package::TooltipLine> numberToTooltipLine;
    numberToTooltipLine.insert(1, Package::TooltipLine::Name);
    numberToTooltipLine.insert(2, Package::TooltipLine::Version);
    numberToTooltipLine.insert(3, Package::TooltipLine::Description);
    numberToTooltipLine.insert(9, Package::TooltipLine::DependsOn);
    return numberToTooltipLine;
}
