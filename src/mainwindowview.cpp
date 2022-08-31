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
#include "qpushbutton.h"
#include "qtconcurrentrun.h"
#include "updatedpackagescolumn.h"

#include <KLocalizedString>
#include <QProcess>
#include <QPointer>
#include <QScopedPointer>
#include <QObject>
#include <QtConcurrent>


MainWindowView::MainWindowView(QWidget *parent)
    : QWidget(parent),
      packages_manager(QSharedPointer<PackagesManager>(new PackagesManager)),
      available_packages_thread(new QThread),
      installed_packages_thread(new QThread),
      updated_packages_thread(new QThread)
{
    m_ui.setupUi(this);
    QObject::connect(available_packages_thread, &QThread::started, [=]() { available_packages_column = QPointer<AvailablePackagesColumn>(new AvailablePackagesColumn(m_ui.available_packages_list)); connectSignalsForAvailablePackages(); });
    QObject::connect(installed_packages_thread, &QThread::started, [=]() { installed_packages_column = QPointer<InstalledPackagesColumn>(new InstalledPackagesColumn(m_ui.installed_packages_list)); connectSignalsForInstalledPackages(); });
    QObject::connect(updated_packages_thread, &QThread::started, [=]() { updated_packages_column = QPointer<UpdatedPackagesColumn>(new UpdatedPackagesColumn(m_ui.packages_to_update_list)); connectSignalsForUpdatedPackages(); });
    QObject::connect(available_packages_thread, &QThread::finished, available_packages_thread, &QThread::deleteLater);
    QObject::connect(installed_packages_thread, &QThread::finished, installed_packages_thread, &QThread::deleteLater);
    QObject::connect(updated_packages_thread, &QThread::finished, updated_packages_thread, &QThread::deleteLater);
    m_ui.available_packages_list->moveToThread(available_packages_thread);
    m_ui.installed_packages_list->moveToThread(installed_packages_thread);
    m_ui.packages_to_update_list->moveToThread(updated_packages_thread);
    available_packages_thread->start();
    installed_packages_thread->start();
    updated_packages_thread->start();
}


MainWindowView::~MainWindowView()
{

}


void MainWindowView::connectSignalsForAvailablePackages()
{
    QObject::connect(m_ui.available_packages_list, &QListWidget::itemChanged, available_packages_column.data(), &AvailablePackagesColumn::updateCheckedPackagesCounter);
    QObject::connect(available_packages_column.data(), &AvailablePackagesColumn::checkedPackagesCounterChanged, [this](bool has_checked_buttons) { m_ui.install_packages_button->setEnabled(has_checked_buttons); });
    QObject::connect(m_ui.install_packages_button, &QPushButton::clicked, [this]() { packages_manager.data()->install(available_packages_column.data()->collectCheckedPackages()); });
    QObject::connect(packages_manager.data(), &PackagesManager::finishedInstall, available_packages_column.data(), &AvailablePackagesColumn::update);
}


void MainWindowView::connectSignalsForInstalledPackages()
{
    QObject::connect(m_ui.installed_packages_list, &QListWidget::itemChanged, installed_packages_column.data(), &InstalledPackagesColumn::updateCheckedPackagesCounter);
    QObject::connect(installed_packages_column.data(), &InstalledPackagesColumn::checkedPackagesCounterChanged, [this](bool has_checked_buttons) { m_ui.uninstall_packages_button->setEnabled(has_checked_buttons); });
    QObject::connect(m_ui.uninstall_packages_button, &QPushButton::clicked, [this]() { packages_manager.data()->uninstall(installed_packages_column.data()->collectCheckedPackages()); });
    QObject::connect(packages_manager.data(), &PackagesManager::finishedUninstall, installed_packages_column.data(), &InstalledPackagesColumn::update);
}


void MainWindowView::connectSignalsForUpdatedPackages()
{
    QObject::connect(m_ui.packages_to_update_list, &QListWidget::itemChanged, updated_packages_column.data(), &UpdatedPackagesColumn::updateCheckedPackagesCounter);
    QObject::connect(updated_packages_column.data(), &UpdatedPackagesColumn::checkedPackagesCounterChanged, [this](bool has_checked_buttons) { m_ui.update_packages_button->setEnabled(has_checked_buttons); });
    QObject::connect(m_ui.update_packages_button, &QPushButton::clicked, [this]() { packages_manager.data()->update(updated_packages_column.data()->collectCheckedPackages()); });
    QObject::connect(packages_manager.data(), &PackagesManager::finishedUpdate, updated_packages_column.data(), &UpdatedPackagesColumn::update);
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

