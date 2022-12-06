#include "updatedpackagescolumn.h"

#include "logger.h"
#include "checkpackage.h"
#include "checkcommandparser.h"

#include <QPointer>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>


UpdatedPackagesColumn::UpdatedPackagesColumn(QListWidget* new_list_widget, QLineEdit* new_search_lineedit, QWidget* new_parent) :
    PackagesColumn(new_list_widget, new_search_lineedit, new_parent),
    current_packages_count(0)
{
    QObject::connect(search_lineedit, &QLineEdit::textEdited, packages_sorter.data(),
                     &Sorter::sortPackagesToUpdateByText);
    QObject::connect(search_lineedit, &QLineEdit::textChanged, packages_sorter.data(),
                     &Sorter::sortPackagesToUpdateByText);
}


QHash<QString, Package::Source> UpdatedPackagesColumn::getPackagesList()
{
    QSharedPointer<CheckCommandParser> command_parser(new CheckCommandParser);
    connect(command_parser.get(), &CheckCommandParser::startOtherThreads, [this]() { emit startOtherThreads(); });
    return command_parser.data()->retrieveInfoMap();
}

// TODO - collect during checking - show warning if there is any package from AUR/POLAUR but not all of them are checked (repo+aur+polaur)
// cause is not possible with pak to update single packages from AUR/POLAUR

void UpdatedPackagesColumn::fill()
{
    packages_sorter->resetOriginalList();
    auto pak_packages = getPackagesList();
    updatePackagesCount(pak_packages.count());
    decltype(pak_packages)::iterator it = pak_packages.begin();
    int i = 0;

    for(;it != pak_packages.end(); it++)
    {
        list_widget->insertItem(i, new CheckPackage(it.key(), it.value()));
        packages_sorter->updateOriginalList(i, new CheckPackage(it.key(), it.value()));
        i++;
    }

    Logger::logger()->logInfo(QStringLiteral("Filled column with %1 packages to update").arg(list_widget->count()));
    list_widget->update();
}


void UpdatedPackagesColumn::toggleAllPackages(bool is_all_checked)
{
    for(int i = 0; i < list_widget->count(); ++i)
    {
        QListWidgetItem* item = list_widget->item(i);
        if (is_all_checked)
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked);
    }
}


void UpdatedPackagesColumn::updatePackagesCount(int new_current_packages_count)
{
    if (current_packages_count != new_current_packages_count)
        emit currentPackagesCountChanged(new_current_packages_count);

    current_packages_count = new_current_packages_count;

}
