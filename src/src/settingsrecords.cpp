#include "settingsrecords.h"

#include "pakGuiSettings.h"
#include "pathconverter.h"


QSettings SettingsRecords::settings(QSettings::NativeFormat, QSettings::UserScope, QString("CachyOS"), QString("pak-gui"));

QColor SettingsRecords::backgroundPreviewColor()
{
    return pakGuiSettings::background_preview_color();
}


QColor SettingsRecords::previewFontColor()
{
    return pakGuiSettings::preview_font_color();
}


QString SettingsRecords::previewFontFamily()
{
    return pakGuiSettings::preview_font_family();
}


QDateTime SettingsRecords::startDateTimeForUpdatesCheck()
{
    return QDateTime::fromString(settings.value("start_datetime_for_updates_check").value<QString>(), "yyyy-M-dThh:mm:ss");
}


QDateTime SettingsRecords::startDateTimeForHistoryStore()
{
    return QDateTime::fromString(settings.value("start_datetime_for_history_store").value<QString>(), "yyyy-M-dThh:mm:ss");
}


QStringList SettingsRecords::packagesInfoAvailable()
{
    if (!settings.value("packages_info_available").value<QStringList>().isEmpty())
        return settings.value("packages_info_available").value<QStringList>();

    return pakGuiSettings::packages_info_available();
}


QStringList SettingsRecords::packagesInfoSelected()
{
    if (!settings.value("packages_info_selected").value<QStringList>().isEmpty())
        return settings.value("packages_info_selected").value<QStringList>();

    return pakGuiSettings::packages_info_selected();
}


QString SettingsRecords::logsFileName()
{
    return pakGuiSettings::logs_filename();
}


QString SettingsRecords::logsFilePath()
{
    return PathConverter::toAbsolutePath(pakGuiSettings::logs_filepath());
}


int SettingsRecords::previewFontSize()
{
    return pakGuiSettings::preview_font_size();
}


int SettingsRecords::historyFileSizeLimitMb()
{
    return pakGuiSettings::history_file_size_limit_in_Mb();
}


int SettingsRecords::historyStoreTimeDays()
{
    return pakGuiSettings::history_store_time_in_days();
}


int SettingsRecords::updateCheckTimeDays()
{
    return pakGuiSettings::update_check_time_in_days();
}


int SettingsRecords::updateCheckTimeHours()
{
    return pakGuiSettings::update_check_time_in_hours();
}


int SettingsRecords::updateCheckTimeMinutes()
{
    return pakGuiSettings::update_check_time_in_minutes();
}


int SettingsRecords::internetReconnectionTimeMinutes()
{
    return pakGuiSettings::internet_reconnection_time_in_minutes();
}


bool SettingsRecords::hideInfoLogs()
{
    return pakGuiSettings::hide_info_logs();
}


bool SettingsRecords::overwriteFullHistoryFile()
{
    return pakGuiSettings::overwrite_full_history_file();
}


bool SettingsRecords::saveLogsIntoFile()
{
    return pakGuiSettings::save_logs_into_file();
}


bool SettingsRecords::showDebug()
{
    return pakGuiSettings::show_debug();
}


bool SettingsRecords::useSystemTray()
{
   return pakGuiSettings::use_system_tray_icon();
}


void SettingsRecords::setAvailablePackageInfo(const QStringList& info)
{
    settings.setValue("packages_info_available", info);
}


void SettingsRecords::setSelectedPackageInfo(const QStringList& info)
{
    if (settings.value("packages_info_selected").value<QStringList>() != info)
        emit selectedPackageInfoListChanged();

    settings.setValue("packages_info_selected", info);
}


void SettingsRecords::setStartDateTimeForUpdatesCheck()
{
    if (settings.value("start_datetime_for_updates_check").value<QString>().isEmpty())
        settings.setValue("start_datetime_for_updates_check", QDateTime::currentDateTime().toString(Qt::ISODate));
}


void SettingsRecords::setStartDateTimeForHistoryStore()
{
    if (settings.value("start_datetime_for_history_store").value<QString>().isEmpty())
        settings.setValue("start_datetime_for_history_store", QDateTime::currentDateTime().toString(Qt::ISODate));
}


void SettingsRecords::resetStartDateTimeForUpdatesCheck()
{
    settings.setValue("start_datetime_for_updates_check", QDateTime::currentDateTime().toString(Qt::ISODate));
}


void SettingsRecords::resetStartDateTimeForHistoryStore()
{
    settings.setValue("start_datetime_for_history_store", QDateTime::currentDateTime().toString(Qt::ISODate));
}
