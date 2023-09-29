// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of tests for  package manager (based on "pak" application).
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

#include "settingstest.h"


TestSettingsWindow::TestSettingsWindow(QObject* parent) :
    QObject{parent},
    settings{&main_window}
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestSettingsWindow::generalDefaultSettingsAreCorrectlyIntroduced()
{
    settings.enableDefaultButton();
    QTest::mouseClick(&*settings.button(QDialogButtonBox::StandardButton::RestoreDefaults), Qt::LeftButton);
    QCOMPARE(settings.general_settings.kcfg_history_store_time_in_days->value(), 0);
    QCOMPARE(settings.general_settings.kcfg_history_file_size_limit_in_Mb->value(), 5);
    QCOMPARE(settings.general_settings.kcfg_internet_reconnection_time_in_minutes->value(), 1);
    QCOMPARE(settings.general_settings.kcfg_update_check_time_in_days->value(), 0);
    QCOMPARE(settings.general_settings.kcfg_update_check_time_in_hours->value(), 6);
    QCOMPARE(settings.general_settings.kcfg_update_check_time_in_minutes->value(), 0);
    QVERIFY(!settings.general_settings.kcfg_overwrite_full_history_file->isChecked());
    QVERIFY(!settings.general_settings.kcfg_use_system_tray_icon->isChecked());
}


void TestSettingsWindow::previewsAppearanceDefaultSettingsAreCorrectlyIntroduced()
{
    settings.enableDefaultButton();
    QTest::mouseClick(&*settings.button(QDialogButtonBox::StandardButton::RestoreDefaults), Qt::LeftButton);
    QCOMPARE(settings.previews_appearance_settings.kcfg_background_preview_color->color(), QColor(Qt::black));
    QCOMPARE(settings.previews_appearance_settings.kcfg_preview_font_color->color(), QColor(Qt::white));
    QCOMPARE(settings.previews_appearance_settings.kcfg_preview_font_family->currentFont().family(), QString("Noto Sans"));
    QCOMPARE(settings.previews_appearance_settings.kcfg_preview_font_size->value(), 15);
}


void TestSettingsWindow::availablePackagesInfoDefaultSettingsAreCorrectlyIntroduced()
{
    settings.enableDefaultButton();
    QTest::mouseClick(&*settings.button(QDialogButtonBox::StandardButton::RestoreDefaults), Qt::LeftButton);
    settings.updateWidgetsDefault();
    QStringList list_packages{};

    for (const auto& available_item : settings.packages_info_settings.packages_info_selector->availableListWidget()->findItems("*", Qt::MatchWildcard))
        list_packages.append(available_item->text());

    QCOMPARE(list_packages.join(','), QString("Architecture,URL,Licenses,Groups,Provides,Optional Deps,RequiredBy,Optional For,Conflicts With,"
                                              "Replaces,Download Size,Installed Size,Packager,Build Date,Install Date,Install Reason,Install Script,Validated By"));
}


void TestSettingsWindow::selectedPackagesInfoDefaultSettingsAreCorrectlyIntroduced()
{
    settings.enableDefaultButton();
    QTest::mouseClick(&*settings.button(QDialogButtonBox::StandardButton::RestoreDefaults), Qt::LeftButton);
    settings.updateWidgetsDefault();
    QStringList list_packages{};

    for (const auto& available_item : settings.packages_info_settings.packages_info_selector->selectedListWidget()->findItems("*", Qt::MatchWildcard))
        list_packages.append(available_item->text());

    QCOMPARE(list_packages.join(','), QString("Name,Version,Description,Depends On"));
}


void TestSettingsWindow::logsDefaultSettingsAreCorrectlyIntroduced()
{
    settings.enableDefaultButton();
    QTest::mouseClick(&*settings.button(QDialogButtonBox::StandardButton::RestoreDefaults), Qt::LeftButton);
    QVERIFY(settings.logs_settings.kcfg_save_logs_into_file->isChecked());
    QCOMPARE(settings.logs_settings.kcfg_logs_filename->text(), QString("logs.txt"));
    QCOMPARE(settings.logs_settings.kcfg_logs_filepath->text(), QString("~/.config/pak-gui"));
    QVERIFY(!settings.logs_settings.kcfg_show_debug->isChecked());
    QVERIFY(!settings.logs_settings.kcfg_hide_info_logs->isChecked());
}


void TestSettingsWindow::applyButtonIsEnabledAfterAnyGeneralSettingChange()
{
    int new_history_store_time_in_days = settings.general_settings.kcfg_history_store_time_in_days->value() + 1;
    settings.general_settings.kcfg_history_store_time_in_days->setValue(new_history_store_time_in_days);
    QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());

    settings.button(QDialogButtonBox::StandardButton::Apply)->setEnabled(false);

    int new_history_file_size_limit_in_Mb = settings.general_settings.kcfg_history_file_size_limit_in_Mb->value() + 1;
    settings.general_settings.kcfg_history_file_size_limit_in_Mb->setValue(new_history_file_size_limit_in_Mb);
    QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());

    settings.button(QDialogButtonBox::StandardButton::Apply)->setEnabled(false);

    int new_internet_reconnection_time_in_minutes = settings.general_settings.kcfg_internet_reconnection_time_in_minutes->value() + 1;
    settings.general_settings.kcfg_internet_reconnection_time_in_minutes->setValue(new_internet_reconnection_time_in_minutes);
    QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());

    settings.button(QDialogButtonBox::StandardButton::Apply)->setEnabled(false);

    int new_update_check_time_in_days = settings.general_settings.kcfg_update_check_time_in_days->value() + 1;
    settings.general_settings.kcfg_update_check_time_in_days->setValue(new_update_check_time_in_days);
    QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());

    settings.button(QDialogButtonBox::StandardButton::Apply)->setEnabled(false);

    int new_update_check_time_in_hours = settings.general_settings.kcfg_update_check_time_in_hours->value() + 1;
    settings.general_settings.kcfg_update_check_time_in_hours->setValue(new_update_check_time_in_hours);
    QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());

    settings.button(QDialogButtonBox::StandardButton::Apply)->setEnabled(false);

    int new_update_check_time_in_minutes = settings.general_settings.kcfg_update_check_time_in_minutes->value() + 1;
    settings.general_settings.kcfg_update_check_time_in_minutes->setValue(new_update_check_time_in_minutes);
    QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());

    settings.button(QDialogButtonBox::StandardButton::Apply)->setEnabled(false);

    QTest::mouseClick(&*settings.general_settings.kcfg_overwrite_full_history_file, Qt::LeftButton);
    QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());

    settings.button(QDialogButtonBox::StandardButton::Apply)->setEnabled(false);

    QTest::mouseClick(&*settings.general_settings.kcfg_use_system_tray_icon, Qt::LeftButton);
    QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());
}


void TestSettingsWindow::applyButtonIsEnabledAfterAnyPreviewsAppearanceSettingChange()
{
    auto current_color = settings.previews_appearance_settings.kcfg_background_preview_color->color();
    settings.previews_appearance_settings.kcfg_background_preview_color->setColor(QColor{Qt::black} == current_color ? QColor{Qt::red} : QColor{Qt::black});
    QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());

    settings.button(QDialogButtonBox::StandardButton::Apply)->setEnabled(false);

    auto current_color_preview = settings.previews_appearance_settings.kcfg_preview_font_color->color();
    settings.previews_appearance_settings.kcfg_preview_font_color->setColor(QColor{Qt::black} == current_color_preview ? QColor{Qt::red} : QColor{Qt::black});
    QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());

    //settings.button(QDialogButtonBox::StandardButton::Apply)->setEnabled(false);

    //auto current_font_family = settings.previews_appearance_settings.kcfg_preview_font_family->font();
    //QFont font("Helvetica");
    //settings.previews_appearance_settings.kcfg_preview_font_family->setFont(font);
    //QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());

    settings.button(QDialogButtonBox::StandardButton::Apply)->setEnabled(false);

    int current_font_size = settings.previews_appearance_settings.kcfg_preview_font_size->value() + 1;
    settings.previews_appearance_settings.kcfg_preview_font_size->setValue(current_font_size);
    QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());
}


void TestSettingsWindow::applyButtonIsEnabledAfterAnyPackagesOrderSettingChange()
{
   auto available_packages = settings.packages_info_settings.packages_info_selector->availableListWidget()->findItems("*", Qt::MatchWildcard);
   emit settings.packages_info_settings.packages_info_selector->movedDown(available_packages.last() - 1);
   QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());

   settings.button(QDialogButtonBox::StandardButton::Apply)->setEnabled(false);

   auto selected_packages = settings.packages_info_settings.packages_info_selector->availableListWidget()->findItems("*", Qt::MatchWildcard);
   emit settings.packages_info_settings.packages_info_selector->movedDown(selected_packages.last() - 1);
   QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());
}


void TestSettingsWindow::applyButtonIsEnabledAfterAnyLogsSettingChange()
{
    QTest::mouseClick(&*settings.logs_settings.kcfg_save_logs_into_file, Qt::LeftButton);
    QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());

    settings.button(QDialogButtonBox::StandardButton::Apply)->setEnabled(false);

    auto new_logs_filename = QString("new_") + settings.logs_settings.kcfg_logs_filename->text();
    settings.logs_settings.kcfg_logs_filename->setText(new_logs_filename);
    QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());

    settings.button(QDialogButtonBox::StandardButton::Apply)->setEnabled(false);

    auto new_logs_filepath = QString("sth/") + settings.logs_settings.kcfg_logs_filepath->text();
    settings.logs_settings.kcfg_logs_filepath->setText(new_logs_filepath);
    QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());

    settings.button(QDialogButtonBox::StandardButton::Apply)->setEnabled(false);

    QTest::mouseClick(&*settings.logs_settings.kcfg_show_debug, Qt::LeftButton);
    QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());

    settings.button(QDialogButtonBox::StandardButton::Apply)->setEnabled(false);

    QTest::mouseClick(&*settings.logs_settings.kcfg_hide_info_logs, Qt::LeftButton);
    QVERIFY(settings.button(QDialogButtonBox::StandardButton::Apply)->isEnabled());
}


void TestSettingsWindow::cleanup()
{
    settings.button(QDialogButtonBox::StandardButton::RestoreDefaults)->setEnabled(false);
    settings.button(QDialogButtonBox::StandardButton::Apply)->setEnabled(false);
}
