#pragma once

#include <QObject>
#include <KConfigDialog>

#include "ui_generalsettings.h"
#include "ui_packagesinfosettings.h"
#include "ui_previewsappearancesettings.h"
#include "ui_logssettings.h"
#include "settingsrecords.h"


class MainWindow;

class Settings : public KConfigDialog
{
    Q_OBJECT
public:
    enum class PackageInfo
    {
        Name = 0,
        Version,
        Description,
        Architecture,
        URL,
        Licenses,
        Groups,
        Provides,
        DependsOn,
        OptionalDeps,
        RequiredBy,
        OptionalFor,
        ConflictsWith,
        Replaces,
        InstalledSize,
        Packager,
        BuildDate,
        InstallDate,
        InstallReason,
        InstallScript,
        ValidatedBy
    };

    explicit Settings(MainWindow* main_window);
    static void saveInitDateTimesWhenEmpty();
    static QSharedPointer<SettingsRecords> records();

private Q_SLOTS:
    void updateWidgetsDefault() override;
    void updateSettings() override;

private:
    void init();
    void loadPackagesInfoSettings();
    void connectSignals();
    void enableDefaultButton();
    void enableButtons();
    void updateAvailableInfoList();
    void updateSelectedInfoList();

    Ui::GeneralSettings general_settings;
    Ui::PreviewsAppearanceSettings previews_appearance_settings;
    Ui::PackagesInfoSettings packages_info_settings;
    Ui::LogsSettings logs_settings;
    static QSharedPointer<SettingsRecords> settings_records;
};
