#include "settings.h"

#include "mainwindow.h"
#include "pakGuiSettings.h"

#include <QListWidget>
#include <QPointer>

Settings::Settings(MainWindow* main_window) :
    KConfigDialog(main_window, QStringLiteral("settings"), pakGuiSettings::self()),
    settings()
{
    qDebug() << "show debug" << pakGuiSettings::show_debug();
    init();
    connectSignals();
    loadPackagesInfoSettings();

    if (packagesInfoNotDefault())
        enableDefaultButton();
}


void Settings::updateWidgetsDefault()
{
    packages_info_settings.packages_info_selector->availableListWidget()->clear();
    packages_info_settings.packages_info_selector->selectedListWidget()->clear();
    packages_info_settings.packages_info_selector->availableListWidget()->addItems(pakGuiSettings::packages_info_available());
    packages_info_settings.packages_info_selector->selectedListWidget()->addItems(pakGuiSettings::packages_info_selected());
}


void Settings::updateSettings()
{
    updateAvailableInfoList();
    updateSelectedInfoList();
}


void Settings::init()
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
    //connect(this, &Settings::settingsChanged, //mainWindowView, &MainWindowView::handleSettingsChanged);
    setAttribute(Qt::WA_DeleteOnClose);
}


void Settings::loadPackagesInfoSettings()
{
    QStringList available_info_list = QStringList();
    QStringList selected_info_list = pakGuiSettings::packages_info_selected();
    available_info_list = !settings.value("packages_info_available").value<QStringList>().isEmpty() ? settings.value("packages_info_available").value<QStringList>() : pakGuiSettings::packages_info_available();
    selected_info_list = !settings.value("packages_info_selected").value<QStringList>().isEmpty() ? settings.value("packages_info_selected").value<QStringList>() : pakGuiSettings::packages_info_selected();
    packages_info_settings.packages_info_selector->availableListWidget()->clear();
    packages_info_settings.packages_info_selector->selectedListWidget()->clear();
    packages_info_settings.packages_info_selector->availableListWidget()->addItems(available_info_list);
    packages_info_settings.packages_info_selector->selectedListWidget()->addItems(selected_info_list);
}


void Settings::connectSignals()
{
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
    enableDefaultButton();
    this->button(QDialogButtonBox::StandardButton::Apply)->setEnabled(true);
}


void Settings::updateAvailableInfoList()
{
    QStringList available_info_list = QStringList();
    for(const auto& available_item : packages_info_settings.packages_info_selector->availableListWidget()->findItems("*", Qt::MatchWildcard))
        available_info_list.append(available_item->text());
    settings.setValue("packages_info_available", available_info_list);
}


void Settings::updateSelectedInfoList()
{
    QStringList selected_info_list = QStringList();
    for(const auto& selected_item : packages_info_settings.packages_info_selector->selectedListWidget()->findItems("*", Qt::MatchWildcard))
        selected_info_list.append(selected_item->text());
    settings.setValue("packages_info_selected", selected_info_list);
}


bool Settings::packagesInfoNotDefault()
{
    auto all_selected_items = settings.value("packages_info_selected").value<QStringList>();

    if (all_selected_items.isEmpty())
        return false;

    if (all_selected_items.count() != pakGuiSettings::packages_info_selected().count())
        return true;

    for(int i = 0; i < all_selected_items.count(); i++)
    {
        if (all_selected_items.at(i) != pakGuiSettings::packages_info_selected().at(i))
            return true;
    }

    return false;
}

