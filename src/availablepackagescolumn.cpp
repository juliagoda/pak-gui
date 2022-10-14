#include "availablepackagescolumn.h"

#include <QObject>
#include <QListWidgetItem>
#include <QPointer>
#include <QMessageBox>

#include "mainwindowview.h"
#include "packagescolumn.h"
#include "qlistwidget.h"
#include "qnamespace.h"
#include "sipackage.h"
#include "sicommandparser.h"


AvailablePackagesColumn::AvailablePackagesColumn(QListWidget* new_list_widget) :
    PackagesColumn(),
    checked_packages{0},
    list_widget{new_list_widget}
{
   fill();
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

        if (item->checkState() == Qt::Checked)
            checked_packages.append(item->getName());
    }

    return checked_packages;
}


void AvailablePackagesColumn::fill()
{
    QStringList pak_packages = getPackagesList();
    QStringList::iterator it = pak_packages.begin();
    int i = 0;

    for(;it != pak_packages.end(); it++)
    {
        list_widget->insertItem(i, new SiPackage(*it));
        i++;
    }

    list_widget->update();
}


void AvailablePackagesColumn::sort(bool is_sorted)
{
    if (is_sorted)
        list_widget->sortItems(Qt::DescendingOrder);
    else
        list_widget->sortItems(Qt::AscendingOrder);

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
