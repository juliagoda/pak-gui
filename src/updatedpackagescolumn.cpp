#include "updatedpackagescolumn.h"

#include <QPointer>
#include <QMessageBox>

#include "checkpackage.h"
#include "checkcommandparser.h"


UpdatedPackagesColumn::UpdatedPackagesColumn(QListWidget* new_list_widget, QLineEdit* new_search_lineedit) :
    PackagesColumn(new_list_widget, new_search_lineedit)
{

}


QStringList UpdatedPackagesColumn::getPackagesList()
{
    QSharedPointer<CheckCommandParser> command_parser(new CheckCommandParser);
    connect(command_parser.get(), &CheckCommandParser::startOtherThreads, [this]() { emit startOtherThreads(); });
    return command_parser.data()->retrieveInfo();
}


QStringList UpdatedPackagesColumn::collectCheckedPackages()
{
    QStringList checked_packages = QStringList();
    for(int i = 0; i < list_widget->count(); ++i)
    {
        CheckPackage* item = dynamic_cast<CheckPackage*>(list_widget->item(i));

        if (item && item->checkState() == Qt::Checked)
            checked_packages.append(item->getName());
    }

    return checked_packages;
}


void UpdatedPackagesColumn::fill()
{
    packages_sorter->resetOriginalList();
    QStringList pak_packages = getPackagesList();
    QStringList::iterator it = pak_packages.begin();
    int i = 0;

    for(;it != pak_packages.end(); it++)
    {
        list_widget->insertItem(i, new CheckPackage(*it));
        packages_sorter->updateOriginalList(i, new CheckPackage(*it));
        i++;
    }

    list_widget->update();
}
