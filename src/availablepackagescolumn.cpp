#include "availablepackagescolumn.h"

#include "packagescolumn.h"
#include "sipackage.h"
#include "sicommandparser.h"
#include "logger.h"

#include <QObject>
#include <QListWidgetItem>
#include <QPointer>
#include <QMessageBox>
#include <QListWidet>


AvailablePackagesColumn::AvailablePackagesColumn(QListWidget* new_list_widget, QLineEdit* new_search_lineedit) :
    PackagesColumn(new_list_widget, new_search_lineedit)
{

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

        if (item && item->checkState() == Qt::Checked)
        {
            Logger::logger()->logDebug(QStringLiteral("Checked package to install: %1").arg(item->getName()));
            checked_packages.append(item->getName());
        }
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

    Logger::logger()->logInfo(QStringLiteral("Filled column with %1 available packages").arg(list_widget->count()));
    list_widget->update();
}
