#include "installedpackagescolumn.h"

#include <QListWidgetItem>
#include <QPointer>
#include <QMessageBox>

#include "qipackage.h"
#include "qicommandparser.h"


InstalledPackagesColumn::InstalledPackagesColumn(QListWidget* new_list_widget, QLineEdit* new_search_lineedit) :
    PackagesColumn(new_list_widget, new_search_lineedit)
{

}


QStringList InstalledPackagesColumn::getPackagesList()
{
    QScopedPointer<QiCommandParser> command_parser(new QiCommandParser);
    return command_parser.data()->retrieveInfo();
}


QStringList InstalledPackagesColumn::collectCheckedPackages()
{
    QStringList checked_packages = QStringList();
    for(int i = 0; i < list_widget->count(); ++i)
    {
        QiPackage* item = dynamic_cast<QiPackage*>(list_widget->item(i));

        if (item && item->checkState() == Qt::Checked)
            checked_packages.append(item->getName());
    }

    return checked_packages;
}


void InstalledPackagesColumn::fill()
{
    packages_sorter->resetOriginalList();
    QStringList pak_packages = getPackagesList();
    QStringList::iterator it = pak_packages.begin();
    int i = 0;

    for(;it != pak_packages.end(); it++)
    {
        QiPackage* package_item = new QiPackage(*it);
        list_widget->insertItem(i, package_item);
        packages_sorter->updateOriginalList(i, new QiPackage(*it));
        i++;
    }

    list_widget->update();
}
