#include "installedpackagescolumn.h"

#include <QListWidgetItem>
#include <QPointer>

#include "qipackage.h"
#include "qicommandparser.h"


InstalledPackagesColumn::InstalledPackagesColumn(QListWidget* new_list_widget) :
    PackagesColumn(),
    pak_packages{getPackagesList()},
    checked_packages{0},
    list_widget{new_list_widget}
{

}

QStringList InstalledPackagesColumn::getPackagesList()
{
    QScopedPointer<QiCommandParser> command_parser(new QiCommandParser);
    return command_parser.data()->retrievePackages();
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
}

void InstalledPackagesColumn::updateCheckedPackagesCounter(QListWidgetItem* package_item)
{
    if (package_item->checkState() == Qt::Checked)
        checked_packages++;
    else
        checked_packages--;

    emit checkedPackagesCounterChanged(checked_packages > 0);
}
