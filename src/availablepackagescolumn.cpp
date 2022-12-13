#include "availablepackagescolumn.h"

#include "packagescolumn.h"
#include "sipackage.h"
#include "sicommandparser.h"
#include "logger.h"

#include <QObject>
#include <QListWidgetItem>
#include <QPointer>
#include <QMessageBox>
#include <QDebug>


AvailablePackagesColumn::AvailablePackagesColumn(QListWidget* new_list_widget, QLineEdit* new_search_lineedit, QWidget* new_parent) :
    PackagesColumn(new_list_widget, new_search_lineedit, new_parent)
{
    QObject::connect(search_lineedit, &QLineEdit::textEdited, packages_sorter.data(),
                     &Sorter::sortAvailablePackagesByText);
    QObject::connect(search_lineedit, &QLineEdit::textChanged, packages_sorter.data(),
                     &Sorter::sortAvailablePackagesByText);
}


QStringList AvailablePackagesColumn::getPackagesList()
{
    QScopedPointer<SiCommandParser> command_parser(new SiCommandParser);
    return command_parser.data()->retrieveInfo();
}


void AvailablePackagesColumn::fill()
{
    packages_sorter->resetOriginalList();
    QStringList pak_packages = getPackagesList();
    emit startOtherThreads();
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
