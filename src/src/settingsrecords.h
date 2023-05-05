#pragma once

#include <QColor>
#include <QFont>
#include <QDateTime>
#include <QString>
#include <QStringList>
#include <QSettings>

#include "package.h"


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
    void resetStartDateTimeForUpdatesCheck();
    void resetStartDateTimeForHistoryStore();

signals:
    void selectedPackageInfoListChanged();

private:
    QMap<QString, Package::TooltipLine> text_to_tooltip_line_map;
    QList<Package::TooltipLine> available_info_list;
    QList<Package::TooltipLine> selected_info_list;
    static QSettings settings;
};

