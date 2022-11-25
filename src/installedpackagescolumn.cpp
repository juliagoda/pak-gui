#include "installedpackagescolumn.h"

#include "qipackage.h"
#include "qicommandparser.h"
#include "logger.h"

#include <QListWidgetItem>
#include <QPointer>
#include <QMessageBox>


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
        {
            Logger::logger()->logDebug(QStringLiteral("Checked package to remove: %1").arg(item->getName()));
            checked_packages.append(item->getName());
        }
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

    Logger::logger()->logInfo(QStringLiteral("Filled column with %1 installed packages").arg(list_widget->count()));
    list_widget->update();
}
