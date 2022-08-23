#include "availablepackagescolumn.h"

#include <QObject>
#include <QListWidgetItem>
#include <QPointer>
#include <QMessageBox>

#include "packagescolumn.h"
#include "qnamespace.h"
#include "sipackage.h"
#include "sicommandparser.h"


AvailablePackagesColumn::AvailablePackagesColumn(QListWidget* new_list_widget) :
    PackagesColumn(),
    pak_packages{getPackagesList()},
    checked_packages{0},
    list_widget{new_list_widget}
{
   fill();
}


QStringList AvailablePackagesColumn::getPackagesList()
{
    QScopedPointer<SiCommandParser> command_parser(new SiCommandParser);
    return command_parser.data()->retrievePackages();
}


QStringList AvailablePackagesColumn::collectCheckedPackages()
{
    QStringList checked_packages = QStringList();
    for(int i = 0; i < list_widget->count(); ++i)
    {
        SiPackage* item = dynamic_cast<SiPackage*>(list_widget->item(i));

        if (item->checkState() == Qt::Checked)
            checked_packages.append(item->getName());
    }

    return checked_packages;
}


void AvailablePackagesColumn::fill()
{
    QStringList::iterator it = pak_packages.begin();
    int i = 0;

    for(;it != pak_packages.end(); it++)
    {
        SiPackage* package_item = new SiPackage(*it);
        list_widget->insertItem(i, package_item);
        i++;
    }

    list_widget->update();
}


void AvailablePackagesColumn::update(int exit_code, QProcess::ExitStatus exit_status)
{
    if (exit_status == QProcess::ExitStatus::CrashExit)
    {
        QMessageBox::warning(new QWidget, tr("Installation"),
                             tr("Packages couln't be installed\n"
                                "Do you want to see logs?"),
                             QMessageBox::Yes | QMessageBox::Cancel);
        return;
    }

    list_widget->clear();
    pak_packages = getPackagesList();
    fill();
    list_widget->update();
}


void AvailablePackagesColumn::updateCheckedPackagesCounter(QListWidgetItem* package_item)
{
    if (package_item->checkState() == Qt::Checked)
        checked_packages++;
    else
        checked_packages--;

    emit checkedPackagesCounterChanged(checked_packages > 0);
}
