#include "updatedpackagescolumn.h"

#include <QPointer>

#include "checkpackage.h"
#include "checkcommandparser.h"

UpdatedPackagesColumn::UpdatedPackagesColumn(QListWidget* new_list_widget) :
    PackagesColumn(),
    pak_packages{getPackagesList()},
    checked_packages{0},
    list_widget{new_list_widget}
{

}


QStringList UpdatedPackagesColumn::getPackagesList()
{
    QScopedPointer<CheckCommandParser> command_parser(new CheckCommandParser);
    return command_parser.data()->retrievePackages();
}


void UpdatedPackagesColumn::fill()
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

void UpdatedPackagesColumn::updateCheckedPackagesCounter(QListWidgetItem* package_item)
{
    if (package_item->checkState() == Qt::Checked)
        checked_packages++;
    else
        checked_packages--;

    emit checkedPackagesCounterChanged(checked_packages > 0);
}
