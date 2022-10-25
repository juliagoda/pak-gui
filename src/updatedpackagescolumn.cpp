#include "updatedpackagescolumn.h"

#include <QPointer>
#include <QMessageBox>

#include "checkpackage.h"
#include "checkcommandparser.h"


UpdatedPackagesColumn::UpdatedPackagesColumn(QListWidget* new_list_widget) :
    PackagesColumn(new_list_widget)
{
   fill();
}


QStringList UpdatedPackagesColumn::getPackagesList()
{
    QScopedPointer<CheckCommandParser> command_parser(new CheckCommandParser);
    return command_parser.data()->retrieveInfo();
}


QStringList UpdatedPackagesColumn::collectCheckedPackages()
{
    QStringList checked_packages = QStringList();
    for(int i = 0; i < list_widget->count(); ++i)
    {
        CheckPackage* item = dynamic_cast<CheckPackage*>(list_widget->item(i));

        if (item->checkState() == Qt::Checked)
            checked_packages.append(item->getName());
    }

    return checked_packages;
}


void UpdatedPackagesColumn::fill()
{
    QStringList pak_packages = getPackagesList();
    QStringList::iterator it = pak_packages.begin();
    int i = 0;

    for(;it != pak_packages.end(); it++)
    {
        list_widget->insertItem(i, new CheckPackage(*it));
        i++;
    }

    list_widget->update();
}
