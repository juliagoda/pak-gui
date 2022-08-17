#include "updatedpackagescolumn.h"

#include <QPointer>
#include <QMessageBox>

#include "checkpackage.h"
#include "checkcommandparser.h"

UpdatedPackagesColumn::UpdatedPackagesColumn(QListWidget* new_list_widget) :
    PackagesColumn(),
    pak_packages{getPackagesList()},
    checked_packages{0},
    list_widget{new_list_widget}
{

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
    QStringList::iterator it = pak_packages.begin();
    int i = 0;

    for(;it != pak_packages.end(); it++)
    {
        CheckPackage* package_item = new CheckPackage(*it);
        list_widget->insertItem(i, package_item);
        i++;
    }
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
    pak_packages = getPackagesList();
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
