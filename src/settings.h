#pragma once

#include <QObject>

#include "ui_generalsettings.h"
#include "ui_packagesinfosettings.h"
#include "ui_previewsappearancesettings.h"
#include "ui_logssettings.h"

class MainWindow;

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(MainWindow* main_window);

private:
    void init(MainWindow* main_window);

    Ui::GeneralSettings general_settings;
    Ui::PreviewsAppearanceSettings previews_appearance_settings;
    Ui::PackagesInfoSettings packages_info_settings;
    Ui::LogsSettings logs_settings;
};

