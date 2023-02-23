#include "settings.h"

#include "logger.h"
#include "mainwindow.h"
#include "pakGuiSettings.h"
#include "settingsrecords.h"

#include <QListWidget>
#include <QPointer>


QSharedPointer<SettingsRecords> Settings::settings_records(new SettingsRecords);

Settings::Settings(MainWindow* main_window) :
    KConfigDialog(main_window, QStringLiteral("settings"), pakGuiSettings::self())
{
    init(main_window);
    connectSignals(main_window);
    loadPackagesInfoSettings();
}


QSharedPointer<SettingsRecords> Settings::records()
{
    return settings_records;
}


void Settings::saveInitDateTime(const QString& operation_name)
{
   if (QString::compare(operation_name, QString("update")) == 0)
       settings_records->resetStartDateTimeForUpdatesCheck();

   if (QString::compare(operation_name, QString("logs remove")) == 0)
       settings_records->resetStartDateTimeForHistoryStore();
}


void Settings::saveInitDateTimesWhenEmpty()
{    
    settings_records->setStartDateTimeForUpdatesCheck();
    settings_records->setStartDateTimeForHistoryStore();
}


void Settings::updateWidgetsDefault()
{
    Logger::logger()->logInfo(QStringLiteral("changed settings to default ones"));
    packages_info_settings.packages_info_selector->availableListWidget()->clear();
    packages_info_settings.packages_info_selector->selectedListWidget()->clear();
    packages_info_settings.packages_info_selector->availableListWidget()->addItems(pakGuiSettings::packages_info_available());
    packages_info_settings.packages_info_selector->selectedListWidget()->addItems(pakGuiSettings::packages_info_selected());
}


void Settings::updateSettings()
{
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
    packages_info_settings.packages_info_selector->availableListWidget()->addItems(settings_records->packagesInfoAvailable());
    packages_info_settings.packages_info_selector->selectedListWidget()->addItems(settings_records->packagesInfoSelected());
}


void Settings::connectSignals(MainWindow* main_window)
{
    connect(settings_records.get(), &SettingsRecords::selectedPackageInfoListChanged, this, [main_window]() { emit main_window->updatedPackageInfoList(); });

    if (!packages_info_settings.packages_info_selector)
        return;

    connect(packages_info_settings.packages_info_selector, &KActionSelector::added, this, [this](QListWidgetItem* item) { Q_UNUSED(item) enableButtons(); });
    connect(packages_info_settings.packages_info_selector, &KActionSelector::removed, this, [this](QListWidgetItem* item) { Q_UNUSED(item) enableButtons(); });
    connect(packages_info_settings.packages_info_selector, &KActionSelector::movedUp, this, [this](QListWidgetItem* item) { Q_UNUSED(item) enableButtons(); });
    connect(packages_info_settings.packages_info_selector, &KActionSelector::movedDown, this, [this](QListWidgetItem* item) { Q_UNUSED(item) enableButtons(); });

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
    for(const auto& available_item : packages_info_settings.packages_info_selector->availableListWidget()->findItems("*", Qt::MatchWildcard))
        available_info_list.append(available_item->text());
    settings_records->setAvailablePackageInfo(available_info_list);
}


void Settings::updateSelectedInfoList()
{
    QStringList selected_info_list = QStringList();
    for(const auto& selected_item : packages_info_settings.packages_info_selector->selectedListWidget()->findItems("*", Qt::MatchWildcard))
        selected_info_list.append(selected_item->text());
    settings_records->setSelectedPackageInfo(selected_info_list);
    Logger::logger()->logDebug(QStringLiteral("selected packages info saved: %1").arg(selected_info_list.join(", ")));
}
