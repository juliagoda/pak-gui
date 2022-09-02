/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// application headers
#include "mainwindowview.h"

#include "availablepackagescolumn.h"
#include "installedpackagescolumn.h"
#include "packagesmanager.h"
#include "pakGuiSettings.h"
#include "qcheckbox.h"
#include "qnamespace.h"
#include "qpushbutton.h"
#include "updatedpackagescolumn.h"

#include <KLocalizedString>
#include <QProcess>
#include <QPointer>
#include <QScopedPointer>
#include <QObject>


MainWindowView::MainWindowView(QWidget *parent)
    : QWidget(parent),
      packages_manager(QSharedPointer<PackagesManager>(new PackagesManager)),
      available_packages_thread(new QThread),
      installed_packages_thread(new QThread),
      updated_packages_thread(new QThread)
{
    m_ui.setupUi(this);

    m_ui.installed_preview_area->hide();
    m_ui.updated_preview_area->hide();
    m_ui.available_preview_area->hide();

   /* m_ui.installed_preview_area->moveToThread(installed_packages_thread);
    m_ui.updated_preview_area->moveToThread(updated_packages_thread);
    m_ui.available_preview_area->moveToThread(available_packages_thread);
    m_ui.packages_available_textarea->moveToThread(available_packages_thread);
    m_ui.available_packages_list->moveToThread(available_packages_thread);*/

    QObject::connect(m_ui.console_view_install, &QCheckBox::toggled, [=](bool is_checked) { if (is_checked) m_ui.available_preview_area->show(); else m_ui.available_preview_area->hide(); });
    QObject::connect(m_ui.console_view_uninstall, &QCheckBox::toggled, [=](bool is_checked) { if (is_checked) m_ui.installed_preview_area->show(); else m_ui.installed_preview_area->hide(); });
    QObject::connect(m_ui.console_view_update, &QCheckBox::toggled, [=](bool is_checked) { if (is_checked) m_ui.updated_preview_area->show(); else m_ui.updated_preview_area->hide(); });

    QObject::connect(available_packages_thread, &QThread::started, [=]() {  available_packages_column = QPointer<AvailablePackagesColumn>(new AvailablePackagesColumn(m_ui.available_packages_list)); connectSignalsForAvailablePackages(); });
    QObject::connect(installed_packages_thread, &QThread::started, [=]() { installed_packages_column = QPointer<InstalledPackagesColumn>(new InstalledPackagesColumn(m_ui.installed_packages_list)); connectSignalsForInstalledPackages(); });
    QObject::connect(updated_packages_thread, &QThread::started, [=]() { updated_packages_column = QPointer<UpdatedPackagesColumn>(new UpdatedPackagesColumn(m_ui.packages_to_update_list)); connectSignalsForUpdatedPackages(); });
    QObject::connect(available_packages_thread, &QThread::finished, available_packages_thread, &QThread::deleteLater);
    QObject::connect(installed_packages_thread, &QThread::finished, installed_packages_thread, &QThread::deleteLater);
    QObject::connect(updated_packages_thread, &QThread::finished, updated_packages_thread, &QThread::deleteLater);


   // m_ui.installed_packages_list->moveToThread(installed_packages_thread);
   // m_ui.packages_to_update_list->moveToThread(updated_packages_thread);

    available_packages_thread->start();
    installed_packages_thread->start();
    updated_packages_thread->start();

    QObject::connect(packages_manager.data(), &PackagesManager::generatedInstallCommandOutput, this, [this](const QString& line) {
        m_ui.packages_installation_textarea->append(line); }, Qt::AutoConnection);
    QObject::connect(packages_manager.data(), &PackagesManager::generatedUninstallCommandOutput, this, [this](const QString& line) {
        m_ui.packages_uninstallation_textarea->append(line); }, Qt::AutoConnection);
    QObject::connect(packages_manager.data(), &PackagesManager::generatedUpdateCommandOutput, this, [this](const QString& line) {
        m_ui.packages_update_textarea->append(line); }, Qt::AutoConnection);

    QObject::connect(packages_manager.data(), &PackagesManager::finishedInstall, available_packages_column.data(), &AvailablePackagesColumn::update, Qt::AutoConnection);
    QObject::connect(packages_manager.data(), &PackagesManager::finishedUninstall, installed_packages_column.data(), &InstalledPackagesColumn::update, Qt::AutoConnection);
    QObject::connect(packages_manager.data(), &PackagesManager::finishedUpdate, updated_packages_column.data(), &UpdatedPackagesColumn::update, Qt::AutoConnection);
}


MainWindowView::~MainWindowView()
{
    if (available_packages_thread->isRunning()) {
        available_packages_thread->quit();
        available_packages_thread->wait();
    }

    if (installed_packages_thread->isRunning()) {
        installed_packages_thread->quit();
        installed_packages_thread->wait();
    }

    if (updated_packages_thread->isRunning()) {
        updated_packages_thread->quit();
        updated_packages_thread->wait();
    }
}


void MainWindowView::connectSignalsForAvailablePackages()
{
    if (m_ui.available_packages_list->count() > 0)
        m_ui.sort_available_packages->setEnabled(true);

    QObject::connect(m_ui.sort_available_packages, &QCheckBox::toggled, available_packages_column.data(), &AvailablePackagesColumn::sort, Qt::AutoConnection);
    QObject::connect(m_ui.available_packages_list, &QListWidget::itemChanged, available_packages_column.data(), &AvailablePackagesColumn::updateCheckedPackagesCounter, Qt::AutoConnection);
    QObject::connect(available_packages_column.data(), &AvailablePackagesColumn::checkedPackagesCounterChanged, this, [this](bool has_checked_buttons) { m_ui.install_packages_button->setEnabled(has_checked_buttons); });
    QObject::connect(m_ui.install_packages_button, &QPushButton::clicked, this, [this]() { m_ui.packages_installation_textarea->clear(); packages_manager.data()->install(available_packages_column.data()->collectCheckedPackages()); }, Qt::AutoConnection);
}


void MainWindowView::connectSignalsForInstalledPackages()
{
    if (m_ui.installed_packages_list->count() > 0)
        m_ui.sort_installed_packages->setEnabled(true);

    QObject::connect(m_ui.sort_installed_packages, &QCheckBox::toggled, installed_packages_column.data(), &InstalledPackagesColumn::sort, Qt::AutoConnection);
    QObject::connect(m_ui.installed_packages_list, &QListWidget::itemChanged, installed_packages_column.data(), &InstalledPackagesColumn::updateCheckedPackagesCounter, Qt::AutoConnection);
    QObject::connect(installed_packages_column.data(), &InstalledPackagesColumn::checkedPackagesCounterChanged, this, [this](bool has_checked_buttons) { m_ui.uninstall_packages_button->setEnabled(has_checked_buttons); }, Qt::AutoConnection);
    QObject::connect(m_ui.uninstall_packages_button, &QPushButton::clicked, this, [this]() { m_ui.packages_uninstallation_textarea->clear(); packages_manager.data()->uninstall(installed_packages_column.data()->collectCheckedPackages()); }, Qt::AutoConnection);
}


void MainWindowView::connectSignalsForUpdatedPackages()
{
    if (m_ui.packages_to_update_list->count() > 0)
        m_ui.sort_packages_to_update->setEnabled(true);

    QObject::connect(m_ui.sort_packages_to_update, &QCheckBox::toggled, updated_packages_column.data(), &UpdatedPackagesColumn::sort, Qt::AutoConnection);
    QObject::connect(m_ui.packages_to_update_list, &QListWidget::itemChanged, updated_packages_column.data(), &UpdatedPackagesColumn::updateCheckedPackagesCounter, Qt::AutoConnection);
    QObject::connect(updated_packages_column.data(), &UpdatedPackagesColumn::checkedPackagesCounterChanged, this, [this](bool has_checked_buttons) { m_ui.update_packages_button->setEnabled(has_checked_buttons); }, Qt::AutoConnection);
    QObject::connect(m_ui.update_packages_button, &QPushButton::clicked, this, [this]() { m_ui.packages_update_textarea->clear(); packages_manager.data()->update(updated_packages_column.data()->collectCheckedPackages()); }, Qt::AutoConnection);
}


void MainWindowView::switchColors()
{
    // switch the foreground/background colors of the label
    QColor color = pakGuiSettings::colorBackground();
    pakGuiSettings::setColorBackground(pakGuiSettings::colorForeground());
    pakGuiSettings::setColorForeground(color);

    handleSettingsChanged();
}


void MainWindowView::handleSettingsChanged()
{
  //  QPalette palette = m_ui.templateLabel->palette();
  //  palette.setColor(QPalette::Window, pakGuiSettings::colorBackground());
  //  palette.setColor(QPalette::WindowText, pakGuiSettings::colorForeground());
  //  m_ui.templateLabel->setPalette(palette);

    // i18n : internationalization
    //  m_ui.templateLabel->setText(i18n("This project is %1 days old", pakGuiSettings::ageInDays()));
}

