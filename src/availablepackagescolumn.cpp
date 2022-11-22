#include "availablepackagescolumn.h"

#include <QObject>
#include <QListWidgetItem>
#include <QPointer>
#include <QMessageBox>

#include "packagescolumn.h"
#include "qlistwidget.h"
#include "qnamespace.h"
#include "sipackage.h"
#include "sicommandparser.h"


AvailablePackagesColumn::AvailablePackagesColumn(QListWidget* new_list_widget, QLineEdit* new_search_lineedit) :
    PackagesColumn(new_list_widget, new_search_lineedit)
{
   fill();
}


QStringList AvailablePackagesColumn::getPackagesList()
{
    QScopedPointer<SiCommandParser> command_parser(new SiCommandParser);
    return command_parser.data()->retrieveInfo();
}


QStringList AvailablePackagesColumn::collectCheckedPackages()
{
    QStringList checked_packages = QStringList();
    for(int i = 0; i < list_widget->count(); ++i)
    {
        SiPackage* item = dynamic_cast<SiPackage*>(list_widget->item(i));

        if (item->checkState() == Qt::Checked)
            checked_packages.append(item->getName());
    }

    return checked_packages;
}


void AvailablePackagesColumn::fill()
{
    packages_sorter->resetOriginalList();
    QStringList pak_packages = getPackagesList();
    QStringList::iterator it = pak_packages.begin();
    int i = 0;

    for(;it != pak_packages.end(); it++)
    {
        list_widget->insertItem(i, new SiPackage(*it));
        packages_sorter->updateOriginalList(i, new SiPackage(*it));
        i++;
    }

    list_widget->update();
}
