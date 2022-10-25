#include "installedpackagescolumn.h"

#include <QListWidgetItem>
#include <QPointer>
#include <QMessageBox>

#include "mainwindowview.h"
#include "qipackage.h"
#include "qicommandparser.h"
#include "qmessagebox.h"


InstalledPackagesColumn::InstalledPackagesColumn(QListWidget* new_list_widget) :
    PackagesColumn(new_list_widget)
{
   fill();
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

        if (item->checkState() == Qt::Checked)
            checked_packages.append(item->getName());
    }

    return checked_packages;
}


void InstalledPackagesColumn::fill()
{
    QStringList pak_packages = getPackagesList();
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
