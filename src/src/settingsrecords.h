// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of  package manager based on "pak" application.
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

#pragma once

#include "package.h"

#include <QColor>
#include <QFont>
#include <QDateTime>
#include <QString>
#include <QStringList>
#include <QSettings>


class SettingsRecords : public QObject
{
    Q_OBJECT

public:
    SettingsRecords();
    ~SettingsRecords() override = default;

    QColor backgroundPreviewColor();
    QColor previewFontColor();
    QString previewFontFamily();

    QDateTime startDateTimeForUpdatesCheck();
    QDateTime startDateTimeForHistoryStore();

    const QList<Package::TooltipLine>& packagesInfoAvailable();
    const QList<Package::TooltipLine>& packagesInfoSelected();
    QStringList packagesInfoAvailableStringList();
    QStringList packagesInfoSelectedStringList();
    QString logsFileName();
    QString logsFilePath();
    QString appStyleName();

    int previewFontSize();
    int historyFileSizeLimitMb();
    int historyStoreTimeDays();
    int updateCheckTimeDays();
    int updateCheckTimeHours();
    int updateCheckTimeMinutes();
    int internetReconnectionTimeMinutes();
    bool hideInfoLogs();
    bool operateOnActionsManually();
    bool overwriteFullHistoryFile();
    bool saveLogsIntoFile();
    bool showDebug();
    bool useSystemTray();

    void setAvailablePackageInfo(const QStringList& info);
    void setSelectedPackageInfo(const QStringList& info);
    void setStartDateTimeForUpdatesCheck();
    void setStartDateTimeForHistoryStore();
    void setAppStyleName(const QString& app_style_name);
    void resetStartDateTimeForUpdatesCheck();
    void resetStartDateTimeForHistoryStore();

signals:
    void selectedPackageInfoListChanged();

private:
    QHash<QString, Package::TooltipLine> text_to_tooltip_line_map;
    QList<Package::TooltipLine> available_info_list;
    QList<Package::TooltipLine> selected_info_list;
    QSettings settings;
};

