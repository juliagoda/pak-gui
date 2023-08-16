// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of CachyOS package manager based on "pak" application.
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

#include "settings.h"

#include "logger.h"
#include "mainwindow.h"
#include "pakGuiSettings.h"
#include "settingsrecords.h"

#include <QListWidget>
#include <QPointer>
#include <algorithm>
#include <iterator>


QSharedPointer<SettingsRecords> Settings::settings_records(nullptr);

Settings::Settings(MainWindow* main_window) :
    KConfigDialog(main_window, QStringLiteral("settings"), pakGuiSettings::self())
{
    init(main_window);
    connectSignals(main_window);
    loadPackagesInfoSettings();
}


const QSharedPointer<SettingsRecords>& Settings::records()
{
    if (settings_records.isNull())
        settings_records.reset(new SettingsRecords);

    return settings_records;
}


void Settings::saveInitDateTime(const QString& operation_name)
{
   if (QString::compare(operation_name, QString("update")) == 0)
       records()->resetStartDateTimeForUpdatesCheck();

   if (QString::compare(operation_name, QString("logs remove")) == 0)
       records()->resetStartDateTimeForHistoryStore();
}


void Settings::clearRecords()
{
   settings_records.reset(nullptr);
}


void Settings::saveInitDateTimesWhenEmpty()
{    
    records()->setStartDateTimeForUpdatesCheck();
    records()->setStartDateTimeForHistoryStore();
}


void Settings::updateWidgetsDefault()
{

#ifdef RUN_TESTS
    return;
#endif

    Logger::logger()->logInfo(QStringLiteral("changed settings to default ones"));
    packages_info_settings.packages_info_selector->availableListWidget()->clear();
    packages_info_settings.packages_info_selector->selectedListWidget()->clear();
    packages_info_settings.packages_info_selector->availableListWidget()->addItems(pakGuiSettings::packages_info_available());
    packages_info_settings.packages_info_selector->selectedListWidget()->addItems(pakGuiSettings::packages_info_selected());
}


void Settings::updateSettings()
{

#ifdef RUN_TESTS
    return;
#endif

    Logger::logger()->logInfo(QStringLiteral("settings have been saved"));
    updateAvailableInfoList();
    updateSelectedInfoList();
}


void Settings::init(MainWindow* main_window)
{
    QPointer<QWidget> general_page = new QWidget;
    general_settings.setupUi(general_page);
    QPointer<QWidget> previews_appearance_page = new QWidget;
    previews_appearance_settings.setupUi(previews_appearance_page);
    QPointer<QWidget> packages_info_page = new QWidget;
    packages_info_settings.setupUi(packages_info_page);
    QPointer<QWidget> logs_page = new QWidget;
    logs_settings.setupUi(logs_page);
    addPage(general_page, i18nc("@title:tab", "General"), QStringLiteral(":/icons/general-settings.png"));
    addPage(previews_appearance_page, i18nc("@title:tab", "Previews appearance"), QStringLiteral(":/icons/general-settings.png"));
    addPage(packages_info_page, i18nc("@title:tab", "Packages informations"), QStringLiteral(":/icons/package-info-settings.png"));
    addPage(logs_page, i18nc("@title:tab", "Logs"), QStringLiteral(":/icons/logs-settings.png"));
    connect(this, &Settings::settingsChanged, main_window, &MainWindow::startSystemTray);
    connect(this, &Settings::settingsChanged, main_window, &MainWindow::setTimersOnChecks);
    setAttribute(Qt::WA_DeleteOnClose);
}


void Settings::loadPackagesInfoSettings()
{
    packages_info_settings.packages_info_selector->availableListWidget()->clear();
    packages_info_settings.packages_info_selector->selectedListWidget()->clear();
    auto available_list = records()->packagesInfoAvailableStringList();
    available_list.removeDuplicates();
    auto selected_list = records()->packagesInfoSelectedStringList();
    selected_list.removeDuplicates();
    packages_info_settings.packages_info_selector->availableListWidget()->addItems(available_list);
    packages_info_settings.packages_info_selector->selectedListWidget()->addItems(selected_list);
}


void Settings::connectSignals(MainWindow* main_window)
{
    connect(records().get(), &SettingsRecords::selectedPackageInfoListChanged, [main_window]() { emit main_window->updatedPackageInfoList(); });

    if (!packages_info_settings.packages_info_selector)
        return;

    connect(packages_info_settings.packages_info_selector, &KActionSelector::added, [this](QListWidgetItem* item) { Q_UNUSED(item) enableButtons(); });
    connect(packages_info_settings.packages_info_selector, &KActionSelector::removed, [this](QListWidgetItem* item) { Q_UNUSED(item) enableButtons(); });
    connect(packages_info_settings.packages_info_selector, &KActionSelector::movedUp, [this](QListWidgetItem* item) { Q_UNUSED(item) enableButtons(); });
    connect(packages_info_settings.packages_info_selector, &KActionSelector::movedDown, [this](QListWidgetItem* item) { Q_UNUSED(item) enableButtons(); });

}


void Settings::enableDefaultButton()
{
    this->button(QDialogButtonBox::StandardButton::RestoreDefaults)->setEnabled(true);
}


void Settings::enableButtons()
{
    Logger::logger()->logDebug(QStringLiteral("enabled buttons in settings after packages info change"));
    enableDefaultButton();
    this->button(QDialogButtonBox::StandardButton::Apply)->setEnabled(true);
}


void Settings::updateAvailableInfoList()
{
    QStringList available_info_list = QStringList();
    auto items = packages_info_settings.packages_info_selector->availableListWidget()->findItems("*", Qt::MatchWildcard);
    std::accumulate(items.begin(), items.end(), &available_info_list, [&](QStringList* list, QListWidgetItem* item)
    {
        if (!list->contains(item->text()))
            list->append(item->text());

        return list;
    });

    records()->setAvailablePackageInfo(available_info_list);
}


void Settings::updateSelectedInfoList()
{
    QStringList selected_info_list = QStringList();
    auto items = packages_info_settings.packages_info_selector->selectedListWidget()->findItems("*", Qt::MatchWildcard);
    std::accumulate(items.begin(), items.end(), &selected_info_list, [&](QStringList* list, QListWidgetItem* item)
    {
        if (!list->contains(item->text()))
            list->append(item->text());

        return list;
    });


    records()->setSelectedPackageInfo(selected_info_list);
    Logger::logger()->logDebug(QStringLiteral("selected packages info saved: %1").arg(selected_info_list.join(", ")));
}
