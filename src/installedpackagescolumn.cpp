#include "installedpackagescolumn.h"

#include <QListWidgetItem>
#include <QPointer>

#include "qipackage.h"
#include "qicommandparser.h"


InstalledPackagesColumn::InstalledPackagesColumn() :
    pak_packages{getPackagesList()}
{

}

QStringList InstalledPackagesColumn::getPackagesList()
{
    QScopedPointer<QiCommandParser> command_parser(new QiCommandParser);
    return command_parser.data()->retrievePackages();
}

void InstalledPackagesColumn::fill(QListWidget* list_widget)
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
