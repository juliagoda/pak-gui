#include "installedpackagescolumn.h"

#include "qipackage.h"
#include "qicommandparser.h"
#include "logger.h"

#include <QListWidgetItem>
#include <QPointer>
#include <QMessageBox>


InstalledPackagesColumn::InstalledPackagesColumn(QListWidget* new_list_widget, QLineEdit* new_search_lineedit, QWidget* new_parent) :
    PackagesColumn(new_list_widget, new_search_lineedit, new_parent)
{
    QObject::connect(search_lineedit, &QLineEdit::textEdited, packages_sorter.data(),
                     &Sorter::sortInstalledPackagesByText);
    QObject::connect(search_lineedit, &QLineEdit::textChanged, packages_sorter.data(),
                     &Sorter::sortInstalledPackagesByText);
}


QStringList InstalledPackagesColumn::getPackagesList()
{
    QScopedPointer<QiCommandParser> command_parser(new QiCommandParser);
    return command_parser.data()->retrieveInfo();
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
        package_item->setNo(i+1);
        list_widget->insertItem(i, package_item);
        QiPackage* package_item_unsorted = new QiPackage(*it);
        package_item_unsorted->setNo(i+1);
        packages_sorter->updateOriginalList(i, package_item_unsorted);
        i++;
    }

    Logger::logger()->logInfo(QStringLiteral("Filled column with %1 installed packages").arg(list_widget->count()));
    list_widget->update();
}
