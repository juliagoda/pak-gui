#include "updatedpackagescolumn.h"

#include <QPointer>

#include "checkpackage.h"
#include "checkcommandparser.h"

UpdatedPackagesColumn::UpdatedPackagesColumn() :
    pak_packages{getPackagesList()}
{

}


QStringList UpdatedPackagesColumn::getPackagesList()
{
    QScopedPointer<CheckCommandParser> command_parser(new CheckCommandParser);
    return command_parser.data()->retrievePackages();
}


void UpdatedPackagesColumn::fill(QListWidget* list_widget)
{
    QStringList::iterator it = pak_packages.begin();
    int i = 0;

    for(;it != pak_packages.end(); it++)
    {
        CheckPackage* package_item = new CheckPackage(*it);
        list_widget->insertItem(i, package_item);
        i++;
    }
}
