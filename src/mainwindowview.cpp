/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// application headers
#include "mainwindowview.h"

#include "pakGuiSettings.h"
#include "package.h"

#include <KLocalizedString>
#include <QProcess>
#include <QPointer>
#include <QScopedPointer>

MainWindowView::MainWindowView(QWidget *parent)
    : QWidget(parent)
{
    m_ui.setupUi(this);
    fillInstalledPackagesColumn(retrievePackagesStringList("-Qi"));
}


MainWindowView::~MainWindowView()
{

}


const QStringList MainWindowView::retrievePackagesStringList(QString pacman_argument)
{
    QScopedPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pacman " + pacman_argument);
    pacman_qi->waitForFinished();
    QString output(pacman_qi->readAllStandardOutput());
    return output.split(QRegularExpression("^\"\"")); // rozdzielać co 21 linijkę
}


void MainWindowView::fillInstalledPackagesColumn(QStringList pacman_packages)
{
    QStringList::iterator it = pacman_packages.begin();
    int i = 0;

    for(;it != pacman_packages.end(); it++)
    {
        QPointer<Package> package(new Package(*it));
        QListWidgetItem* package_item = new QListWidgetItem;
        package_item->setText(package->getName() + "-" + package->getVersion());
        m_ui.installed_packages_list->insertItem(i, package_item);
        i++;
    }
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

