#include "updatedpackagescolumn.h"
#include "logger.h"
#include "checkpackage.h"
#include "checkcommandparser.h"

#include <QPointer>
#include <QMessageBox>


UpdatedPackagesColumn::UpdatedPackagesColumn(QListWidget* new_list_widget, QLineEdit* new_search_lineedit) :
    PackagesColumn(new_list_widget, new_search_lineedit)
{
    QObject::connect(search_lineedit, &QLineEdit::textEdited, packages_sorter.data(),
                     &Sorter::sortPackagesToUpdateByText);
    QObject::connect(search_lineedit, &QLineEdit::textChanged, packages_sorter.data(),
                     &Sorter::sortPackagesToUpdateByText);
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
        {
            Logger::logger()->logDebug(QStringLiteral("Checked package to update: %1").arg(item->getName().trimmed()));
            checked_packages.append(item->getName().trimmed());
        }
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

    Logger::logger()->logInfo(QStringLiteral("Filled column with %1 packages to update").arg(list_widget->count()));
    list_widget->update();
}
