#include "installedpackagescolumn.h"

#include <QListWidgetItem>
#include <QPointer>
#include <QMessageBox>

#include "qipackage.h"
#include "qicommandparser.h"
#include "qmessagebox.h"


InstalledPackagesColumn::InstalledPackagesColumn(QListWidget* new_list_widget, QTextBrowser* new_packages_installation_textarea) :
    PackagesColumn(),
    checked_packages{0},
    list_widget{new_list_widget},
    packages_installation_textarea{new_packages_installation_textarea},
    pak_packages{getPackagesList()}
{
   fill();
}


QStringList InstalledPackagesColumn::getPackagesList()
{
    QScopedPointer<QiCommandParser> command_parser(new QiCommandParser(packages_installation_textarea));
    return command_parser.data()->retrievePackages();
}


QStringList InstalledPackagesColumn::collectCheckedPackages()
{
    QStringList checked_packages = QStringList();
    for(int i = 0; i < list_widget->count(); ++i)
    {
        QiPackage* item = dynamic_cast<QiPackage*>(list_widget->item(i));

        if (item->checkState() == Qt::Checked)
            checked_packages.append(item->getName());
    }

    return checked_packages;
}


void InstalledPackagesColumn::fill()
{
    QStringList::iterator it = pak_packages.begin();
    int i = 0;

    for(;it != pak_packages.end(); it++)
    {
        QiPackage* package_item = new QiPackage(*it);
        list_widget->insertItem(i, package_item);
        i++;
    }

    list_widget->update();
}


void InstalledPackagesColumn::sort(bool is_sorted)
{
    if (is_sorted)
        list_widget->sortItems(Qt::DescendingOrder);
    else
        list_widget->sortItems(Qt::AscendingOrder);

    list_widget->update();
}


void InstalledPackagesColumn::update(int exit_code, QProcess::ExitStatus exit_status)
{
    if (exit_status == QProcess::ExitStatus::CrashExit)
    {
        QMessageBox::warning(new QWidget, tr("Uninstallation"),
                             tr("Packages couln't be removed\n"
                                "Do you want to see logs?"),
                             QMessageBox::Yes | QMessageBox::Cancel);
        return;
    }

   list_widget->clear();
   pak_packages = getPackagesList();
   fill();
   list_widget->update();
}


void InstalledPackagesColumn::updateCheckedPackagesCounter(QListWidgetItem* package_item)
{
    if (package_item->checkState() == Qt::Checked)
        checked_packages++;
    else
        checked_packages--;

    emit checkedPackagesCounterChanged(checked_packages > 0);
}
