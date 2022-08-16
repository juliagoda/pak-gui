#include "availablepackagescolumn.h"

#include <QListWidgetItem>
#include <QPointer>

#include "sipackage.h"
#include "sicommandparser.h"


AvailablePackagesColumn::AvailablePackagesColumn() :
    pak_packages{getPackagesList()}
{

}

QStringList AvailablePackagesColumn::getPackagesList()
{
    QScopedPointer<SiCommandParser> command_parser(new SiCommandParser);
    return command_parser.data()->retrievePackages();
}

void AvailablePackagesColumn::fill(QListWidget* list_widget)
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
