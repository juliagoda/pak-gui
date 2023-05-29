#include "installedpackagescolumn.h"

#include "qipackage.h"
#include "qicommandparser.h"
#include "logger.h"

#include <QListWidgetItem>
#include <QPointer>
#include <QMessageBox>


InstalledPackagesColumn::InstalledPackagesColumn(QListWidget* new_list_widget,
                                                 QLineEdit* new_search_lineedit,
                                                 QCheckBox* new_reverse_sort_checkbox,
                                                 QWidget* new_parent) :
    PackagesColumn(new_list_widget, new_search_lineedit, new_reverse_sort_checkbox, new_parent)
{
    if (!search_lineedit)
        return;

    QObject::connect(search_lineedit, &QLineEdit::textEdited, packages_sorter.data(),
                     [&](const QString& text) { packages_sorter->sortPackagesByText<QiPackage>(text, QiPackage{""}); });
    QObject::connect(search_lineedit, &QLineEdit::textChanged, packages_sorter.data(),
                     [&](const QString& text) { packages_sorter->sortPackagesByText<QiPackage>(text, QiPackage{""}); });
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
        package_item->setNo(i + 1);
        list_widget->insertItem(i, package_item);
        i++;
    }

    Logger::logger()->logInfo(QStringLiteral("Filled column with %1 installed packages").arg(list_widget->count()));
    list_widget->update();
}
