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

#include <KConfigDialog>

#include <mutex>

#include "ui_generalsettings.h"
#include "ui_packagesinfosettings.h"
#include "ui_previewsappearancesettings.h"
#include "ui_logssettings.h"
#include "ui_appstylesettings.h"

#include "settingsrecords.h"


class MainWindow;

class Settings : public KConfigDialog
{
    Q_OBJECT

public:
    explicit Settings(MainWindow* main_window);
    ~Settings() override;

    static void saveInitDateTimesWhenEmpty();
    static const QScopedPointer<SettingsRecords>& records();
    static void saveInitDateTime(const QString& operation_name);
    static void clearRecords();

protected Q_SLOTS:
    void updateWidgetsDefault() override;
    void updateSettings() override;
    void saveAppStyle();

protected:
    virtual void loadPackagesInfoSettings();
    void enableDefaultButton();

    Ui::GeneralSettings general_settings;
    Ui::PreviewsAppearanceSettings previews_appearance_settings;
    Ui::PackagesInfoSettings packages_info_settings;
    Ui::LogsSettings logs_settings;
    Ui::AppStyleSettings styles_settings;
    static QScopedPointer<SettingsRecords> settings_records;
    MainWindow* main_window = nullptr;

private:
    void init(MainWindow* main_window);
    void connectSignals(MainWindow* main_window);
    void enableButtons();
    void updateAvailableInfoList();
    void updateSelectedInfoList();

    std::once_flag restart_app_for_style;
};
