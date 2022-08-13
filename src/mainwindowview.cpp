/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// application headers
#include "mainwindowview.h"

#include "pakGuiSettings.h"
#include "packagefromdescription.h"
#include "packagefromlist.h"

#include <KLocalizedString>
#include <QProcess>
#include <QPointer>
#include <QScopedPointer>


MainWindowView::MainWindowView(QWidget *parent)
    : QWidget(parent)
{
    m_ui.setupUi(this);
    fillInstalledPackagesColumn(m_ui.installed_packages_list, retrievePackagesStringList("-Qi"));
    fillInstalledPackagesColumn(m_ui.available_packages_list, retrievePackagesStringList("-Si"));
    fillUpdatedPackagesColumn(retrievePackagesToUpdateStringList());
}


MainWindowView::~MainWindowView()
{

}


const QStringList MainWindowView::retrievePackagesStringList(QString pacman_argument)
{
    QScopedPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak " + pacman_argument);
    pacman_qi->waitForFinished();
    QString output(pacman_qi->readAllStandardOutput());
    return output.split(QRegularExpression("Validated By[^\n]*\n\n"));
}


const QStringList MainWindowView::retrievePackagesToUpdateStringList()
{
    QScopedPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -C");
    pacman_qi->waitForFinished();
    QString output(pacman_qi->readAllStandardOutput());

    QStringList system_packages = QStringList();
    QStringList output_list = output.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
    QStringListIterator it(output_list);

    while (it.hasNext())
    {
        QString line = it.next();
        if (line.contains("=>"))
        {
           system_packages.append(line.simplified());
        }
    }

    return system_packages;
}


void MainWindowView::fillInstalledPackagesColumn(QListWidget* packages_column, QStringList pacman_packages)
{
    QStringList::iterator it = pacman_packages.begin();
    int i = 0;

    for(;it != pacman_packages.end(); it++)
    {
        QPointer<PackageFromDescription> package(new PackageFromDescription(*it));
        QListWidgetItem* package_item = new QListWidgetItem;
        package_item->setText(package->getName() + "-" + package->getVersion());
        packages_column->insertItem(i, package_item);
        i++;
    }
}


void MainWindowView::fillUpdatedPackagesColumn(QStringList pacman_packages)
{
    QStringList::iterator it = pacman_packages.begin();
    int i = 0;

    for(;it != pacman_packages.end(); it++)
    {
        QPointer<PackageFromList> package(new PackageFromList(*it));
        QListWidgetItem* package_item = new QListWidgetItem;
        package_item->setText(package->getName() + "-" + package->getVersion());
        m_ui.packages_to_update_list->insertItem(i, package_item);
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

