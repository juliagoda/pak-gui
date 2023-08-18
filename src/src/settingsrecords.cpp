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

#include "settingsrecords.h"

#include "pakGuiSettings.h"
#include "pathconverter.h"

#include <KLocalizedString>


QSettings SettingsRecords::settings(QSettings::NativeFormat, QSettings::UserScope, QString("CachyOS"), QString("pak-gui"));

SettingsRecords::SettingsRecords()
{
    if (!text_to_tooltip_line_map.isEmpty())
        return;

    text_to_tooltip_line_map.insert("Name", Package::TooltipLine::Name);
    text_to_tooltip_line_map.insert("Version", Package::TooltipLine::Version);
    text_to_tooltip_line_map.insert("Description", Package::TooltipLine::Description);
    text_to_tooltip_line_map.insert("Architecture", Package::TooltipLine::Architecture);
    text_to_tooltip_line_map.insert("Provides", Package::TooltipLine::Provides);
    text_to_tooltip_line_map.insert("URL", Package::TooltipLine::URL);
    text_to_tooltip_line_map.insert("Licenses", Package::TooltipLine::Licenses);
    text_to_tooltip_line_map.insert("Groups", Package::TooltipLine::Groups);
    text_to_tooltip_line_map.insert("Depends On", Package::TooltipLine::DependsOn);
    text_to_tooltip_line_map.insert("Optional Deps", Package::TooltipLine::OptionalDeps);
    text_to_tooltip_line_map.insert("Required By", Package::TooltipLine::RequiredBy);
    text_to_tooltip_line_map.insert("Optional For", Package::TooltipLine::OptionalFor);
    text_to_tooltip_line_map.insert("Conflicts With", Package::TooltipLine::ConflictsWith);
    text_to_tooltip_line_map.insert("Replaces", Package::TooltipLine::Replaces);
    text_to_tooltip_line_map.insert("Installed Size", Package::TooltipLine::InstalledSize);
    text_to_tooltip_line_map.insert("Packager", Package::TooltipLine::Packager);
    text_to_tooltip_line_map.insert("Build Date", Package::TooltipLine::BuildDate);
    text_to_tooltip_line_map.insert("Install Date", Package::TooltipLine::InstallDate);
    text_to_tooltip_line_map.insert("Install Reason", Package::TooltipLine::InstallReason);
    text_to_tooltip_line_map.insert("Install Script", Package::TooltipLine::InstallScript);
    text_to_tooltip_line_map.insert("Validated By", Package::TooltipLine::ValidatedBy);
    text_to_tooltip_line_map.insert("Download Size", Package::TooltipLine::DownloadSize);
}


QColor SettingsRecords::backgroundPreviewColor()
{

#ifdef RUN_TESTS
    return QColor(Qt::black);
#endif

    return pakGuiSettings::background_preview_color();
}


QColor SettingsRecords::previewFontColor()
{

#ifdef RUN_TESTS
    return QColor(Qt::white);
#endif

    return pakGuiSettings::preview_font_color();
}


QString SettingsRecords::previewFontFamily()
{

#ifdef RUN_TESTS
    return QString("DejaVu Sans");
#endif

    return pakGuiSettings::preview_font_family();
}


QDateTime SettingsRecords::startDateTimeForUpdatesCheck()
{

#ifdef RUN_TESTS
    return QDateTime::currentDateTime();
#endif

    return QDateTime::fromString(settings.value("start_datetime_for_updates_check").value<QString>(), "yyyy-M-dThh:mm:ss");
}


QDateTime SettingsRecords::startDateTimeForHistoryStore()
{

#ifdef RUN_TESTS
    return QDateTime::currentDateTime();
#endif

    return QDateTime::fromString(settings.value("start_datetime_for_history_store").value<QString>(), "yyyy-M-dThh:mm:ss");
}


const QList<Package::TooltipLine>& SettingsRecords::packagesInfoAvailable()
{
    if (available_info_list.isEmpty())
    {
        for (const auto& info_item : packagesInfoAvailableStringList())
            available_info_list.append(text_to_tooltip_line_map.value(info_item));
    }

   return available_info_list;
}


const QList<Package::TooltipLine>& SettingsRecords::packagesInfoSelected()
{
    if (selected_info_list.isEmpty())
    {
        for (const auto& info_item : packagesInfoSelectedStringList())
        {
            qDebug() << "info_item: " << info_item;
            selected_info_list.append(text_to_tooltip_line_map.value(info_item));
        }
    }

   return selected_info_list;
}


QStringList SettingsRecords::packagesInfoAvailableStringList()
{

#ifdef RUN_TESTS
    return QString("Architecture,URL,Licenses,Groups,Provides,Optional Deps,RequiredBy,Optional For,Conflicts With,"
                   "Replaces,Download Size,Installed Size,Packager,Build Date,Install Date,Install Reason,Install Script,Validated By").split(',');
#endif

    if (!settings.value("packages_info_available").value<QStringList>().isEmpty())
        return settings.value("packages_info_available").value<QStringList>();

    return pakGuiSettings::packages_info_available();
}


QStringList SettingsRecords::packagesInfoSelectedStringList()
{

#ifdef RUN_TESTS
    return QString("Name,Version,Description,Depends On").split(',');
#endif

    if (!settings.value("packages_info_selected").value<QStringList>().isEmpty())
        return settings.value("packages_info_selected").value<QStringList>();

    return pakGuiSettings::packages_info_selected();
}


QString SettingsRecords::logsFileName()
{

#ifdef RUN_TESTS
    return QString("logs.txt");
#endif

    return pakGuiSettings::logs_filename();
}


QString SettingsRecords::logsFilePath()
{

#ifdef RUN_TESTS
    return QString("~/.config/pak-gui");
#endif

    return PathConverter::toAbsolutePath(pakGuiSettings::logs_filepath());
}


int SettingsRecords::previewFontSize()
{

#ifdef RUN_TESTS
    return 15;
#endif

    return pakGuiSettings::preview_font_size();
}


int SettingsRecords::historyFileSizeLimitMb()
{

#ifdef RUN_TESTS
    return 5;
#endif

    return pakGuiSettings::history_file_size_limit_in_Mb();
}


int SettingsRecords::historyStoreTimeDays()
{

#ifdef RUN_TESTS
    return 0;
#endif

    return pakGuiSettings::history_store_time_in_days();
}


int SettingsRecords::updateCheckTimeDays()
{

#ifdef RUN_TESTS
    return 0;
#endif

    return pakGuiSettings::update_check_time_in_days();
}


int SettingsRecords::updateCheckTimeHours()
{

#ifdef RUN_TESTS
    return 6;
#endif

    return pakGuiSettings::update_check_time_in_hours();
}


int SettingsRecords::updateCheckTimeMinutes()
{

#ifdef RUN_TESTS
    return 0;
#endif

    return pakGuiSettings::update_check_time_in_minutes();
}


int SettingsRecords::internetReconnectionTimeMinutes()
{

#ifdef RUN_TESTS
    return 1;
#endif

    return pakGuiSettings::internet_reconnection_time_in_minutes();
}


bool SettingsRecords::hideInfoLogs()
{

#ifdef RUN_TESTS
    return false;
#endif

    return pakGuiSettings::hide_info_logs();
}


bool SettingsRecords::operateOnActionsManually()
{

#ifdef RUN_TESTS
    return false;
#endif

    return pakGuiSettings::manual_operations_checkbox();
}


bool SettingsRecords::overwriteFullHistoryFile()
{

#ifdef RUN_TESTS
    return false;
#endif

    return pakGuiSettings::overwrite_full_history_file();
}


bool SettingsRecords::saveLogsIntoFile()
{

#ifdef RUN_TESTS
    return true;
#endif

    return pakGuiSettings::save_logs_into_file();
}


bool SettingsRecords::showDebug()
{

#ifdef RUN_TESTS
    return false;
#endif

    return pakGuiSettings::show_debug();
}


bool SettingsRecords::useSystemTray()
{

#ifdef RUN_TESTS
    return true;
#endif

    return pakGuiSettings::use_system_tray_icon();
}


void SettingsRecords::setAvailablePackageInfo(const QStringList& info)
{

#ifdef RUN_TESTS
    return;
#endif

    available_info_list.clear();
    for (const auto& info_item : info)
        available_info_list.append(text_to_tooltip_line_map.value(info_item));

    settings.setValue("packages_info_available", info);
}


void SettingsRecords::setSelectedPackageInfo(const QStringList& info)
{

#ifdef RUN_TESTS
    return;
#endif

    selected_info_list.clear();
    for (const auto& info_item : info)
        selected_info_list.append(text_to_tooltip_line_map.value(info_item));

    if (settings.value("packages_info_selected").value<QStringList>() != info)
        emit selectedPackageInfoListChanged();

    settings.setValue("packages_info_selected", info);
}


void SettingsRecords::setStartDateTimeForUpdatesCheck()
{

#ifdef RUN_TESTS
    return;
#endif

    if (settings.value("start_datetime_for_updates_check").value<QString>().isEmpty())
        settings.setValue("start_datetime_for_updates_check", QDateTime::currentDateTime().toString(Qt::ISODate));
}


void SettingsRecords::setStartDateTimeForHistoryStore()
{

#ifdef RUN_TESTS
    return;
#endif

    if (settings.value("start_datetime_for_history_store").value<QString>().isEmpty())
        settings.setValue("start_datetime_for_history_store", QDateTime::currentDateTime().toString(Qt::ISODate));
}


void SettingsRecords::resetStartDateTimeForUpdatesCheck()
{

#ifdef RUN_TESTS
    return;
#endif

    settings.setValue("start_datetime_for_updates_check", QDateTime::currentDateTime().toString(Qt::ISODate));
}


void SettingsRecords::resetStartDateTimeForHistoryStore()
{

#ifdef RUN_TESTS
    return;
#endif

    settings.setValue("start_datetime_for_history_store", QDateTime::currentDateTime().toString(Qt::ISODate));
}
