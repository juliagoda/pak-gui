/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// application headers
#include "mainwindowview.h"

#include "packagesmanager.h"
#include "pakGuiSettings.h"
#include "qpushbutton.h"

#include <KLocalizedString>
#include <QProcess>
#include <QPointer>
#include <QScopedPointer>
#include <QObject>


MainWindowView::MainWindowView(QWidget *parent)
    : QWidget(parent),
      packages_manager(QSharedPointer<PackagesManager>(new PackagesManager))
{
    m_ui.setupUi(this);
    available_packages_column = QPointer<AvailablePackagesColumn>(new AvailablePackagesColumn(m_ui.available_packages_list));
    installed_packages_column = QPointer<InstalledPackagesColumn>(new InstalledPackagesColumn(m_ui.installed_packages_list));
    updated_packages_column = QPointer<UpdatedPackagesColumn>(new UpdatedPackagesColumn(m_ui.packages_to_update_list));
    fillColumns();
    connectSignals();
}


MainWindowView::~MainWindowView()
{

}


void MainWindowView::fillColumns()
{
   available_packages_column.data()->fill();
   installed_packages_column.data()->fill();
   updated_packages_column.data()->fill();
}


void MainWindowView::connectSignals()
{
   QObject::connect(m_ui.available_packages_list, &QListWidget::itemChanged, available_packages_column.data(), &AvailablePackagesColumn::updateCheckedPackagesCounter);
   QObject::connect(available_packages_column.data(), &AvailablePackagesColumn::checkedPackagesCounterChanged, [this](bool has_checked_buttons) { m_ui.install_packages_button->setEnabled(has_checked_buttons); });
   QObject::connect(m_ui.install_packages_button, &QPushButton::clicked, [this]() { packages_manager.data()->install(available_packages_column.data()->collectCheckedPackages()); });
   QObject::connect(packages_manager.data(), &PackagesManager::finishedInstall, available_packages_column.data(), &AvailablePackagesColumn::update);

   QObject::connect(m_ui.installed_packages_list, &QListWidget::itemChanged, installed_packages_column.data(), &InstalledPackagesColumn::updateCheckedPackagesCounter);
   QObject::connect(installed_packages_column.data(), &InstalledPackagesColumn::checkedPackagesCounterChanged, [this](bool has_checked_buttons) { m_ui.uninstall_packages_button->setEnabled(has_checked_buttons); });
   QObject::connect(m_ui.uninstall_packages_button, &QPushButton::clicked, [this]() { packages_manager.data()->uninstall(installed_packages_column.data()->collectCheckedPackages()); });
   QObject::connect(packages_manager.data(), &PackagesManager::finishedUninstall, installed_packages_column.data(), &InstalledPackagesColumn::update);

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

