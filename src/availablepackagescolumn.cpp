#include "availablepackagescolumn.h"

#include <QObject>
#include <QListWidgetItem>
#include <QPointer>

#include "packagescolumn.h"
#include "sipackage.h"
#include "sicommandparser.h"


AvailablePackagesColumn::AvailablePackagesColumn(QListWidget* new_list_widget) :
    PackagesColumn(),
    pak_packages{getPackagesList()},
    checked_packages{0},
    list_widget{new_list_widget}
{

}

QStringList AvailablePackagesColumn::getPackagesList()
{
    QScopedPointer<SiCommandParser> command_parser(new SiCommandParser);
    return command_parser.data()->retrievePackages();
}

void AvailablePackagesColumn::fill()
{
    QStringList::iterator it = pak_packages.begin();
    int i = 0;

    for(;it != pak_packages.end(); it++)
    {
        SiPackage* package_item = new SiPackage(*it);
        list_widget->insertItem(i, package_item);
        i++;
    }
}

void AvailablePackagesColumn::updateCheckedPackagesCounter(QListWidgetItem* package_item)
{
    if (package_item->checkState() == Qt::Checked)
        checked_packages++;
    else
        checked_packages--;

    emit checkedPackagesCounterChanged(checked_packages > 0);
}
