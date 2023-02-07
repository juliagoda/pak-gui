#pragma once

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
    SettingsRecords() = default;
    ~SettingsRecords() override = default;

    QColor backgroundPreviewColor();
    QColor previewFontColor();
    QString previewFontFamily();

    QDateTime startDateTimeForUpdatesCheck();
    QDateTime startDateTimeForHistoryStore();

    QStringList packagesInfoAvailable();
    QStringList packagesInfoSelected();
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
    static QSettings settings;
};

