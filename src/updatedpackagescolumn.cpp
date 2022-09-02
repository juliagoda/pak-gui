#include "updatedpackagescolumn.h"

#include <QPointer>
#include <QMessageBox>

#include "checkpackage.h"
#include "checkcommandparser.h"


UpdatedPackagesColumn::UpdatedPackagesColumn(QListWidget* new_list_widget) :
    PackagesColumn(),
    checked_packages{0},
    list_widget{new_list_widget}
{
   fill();
}


QStringList UpdatedPackagesColumn::getPackagesList()
{
    QScopedPointer<CheckCommandParser> command_parser(new CheckCommandParser);
    return command_parser.data()->retrievePackages();
}


QStringList UpdatedPackagesColumn::collectCheckedPackages()
{
    QStringList checked_packages = QStringList();
    for(int i = 0; i < list_widget->count(); ++i)
    {
        CheckPackage* item = dynamic_cast<CheckPackage*>(list_widget->item(i));

        if (item->checkState() == Qt::Checked)
            checked_packages.append(item->getName());
    }

    return checked_packages;
}


void UpdatedPackagesColumn::fill()
{
    QStringList pak_packages = getPackagesList();
    QStringList::iterator it = pak_packages.begin();
    int i = 0;

    for(;it != pak_packages.end(); it++)
    {
        list_widget->insertItem(i, new CheckPackage(*it));
        i++;
    }

    list_widget->update();
}


void UpdatedPackagesColumn::sort(bool is_sorted)
{
    if (is_sorted)
        list_widget->sortItems(Qt::DescendingOrder);
    else
        list_widget->sortItems(Qt::AscendingOrder);

    list_widget->update();
}


void UpdatedPackagesColumn::update(int exit_code, QProcess::ExitStatus exit_status)
{
    if (exit_status == QProcess::ExitStatus::CrashExit)
    {
        QMessageBox::warning(new QWidget, tr("Update"),
                             tr("Packages couln't be updated\n"
                                "Do you want to see logs?"),
                             QMessageBox::Yes | QMessageBox::Cancel);
        return;
    }

    list_widget->clear();
    fill();
    list_widget->update();
}


void UpdatedPackagesColumn::updateCheckedPackagesCounter(QListWidgetItem* package_item)
{
    if (package_item->checkState() == Qt::Checked)
        checked_packages++;
    else
        checked_packages--;

    emit checkedPackagesCounterChanged(checked_packages > 0);
}
