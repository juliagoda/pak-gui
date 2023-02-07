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
    explicit Settings(MainWindow* main_window);
    ~Settings() override = default;
    static void saveInitDateTimesWhenEmpty();
    static QSharedPointer<SettingsRecords> records();
    static void saveInitDateTime(const QString& operation_name);

protected Q_SLOTS:
    void updateWidgetsDefault() override;
    void updateSettings() override;

protected:
    virtual void loadPackagesInfoSettings();
    void enableDefaultButton();

    Ui::GeneralSettings general_settings;
    Ui::PreviewsAppearanceSettings previews_appearance_settings;
    Ui::PackagesInfoSettings packages_info_settings;
    Ui::LogsSettings logs_settings;
    static QSharedPointer<SettingsRecords> settings_records;

private:
    void init(MainWindow* main_window);
    void connectSignals(MainWindow* main_window);
    void enableButtons();
    void updateAvailableInfoList();
    void updateSelectedInfoList();
};
