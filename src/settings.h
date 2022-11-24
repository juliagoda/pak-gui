#pragma once

#include <QObject>
#include <KConfigDialog>
#include <QSettings>

#include "ui_generalsettings.h"
#include "ui_packagesinfosettings.h"
#include "ui_previewsappearancesettings.h"
#include "ui_logssettings.h"

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
    bool packagesInfoNotDefault();

    Ui::GeneralSettings general_settings;
    Ui::PreviewsAppearanceSettings previews_appearance_settings;
    Ui::PackagesInfoSettings packages_info_settings;
    Ui::LogsSettings logs_settings;
    QSettings settings;
};

struct DefaultPackagesInfo
{
    QStringList packages_info_selected = QStringList() << QString("Name") <<
                                                           QString("Version") <<
                                                           QString("Description") <<
                                                           QString("Depends On");
    QStringList packages_info_available = QStringList() << QString("Architecture") <<
                                                          QString("URL") <<
                                                          QString("Licenses") <<
                                                          QString("Groups") <<
                                                          QString("Provides") <<
                                                          QString("Optional Deps") <<
                                                          QString("Required By") <<
                                                          QString("Optional For") <<
                                                          QString("Conflicts With") <<
                                                          QString("Replaces") <<
                                                          QString("Installed Size") <<
                                                          QString("Packager") <<
                                                          QString("Build Date") <<
                                                          QString("Install Date") <<
                                                          QString("Install Reason") <<
                                                          QString("Install Script") <<
                                                          QString("Validated By");

};
