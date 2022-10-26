#include "packagescolumn.h"


PackagesColumn::PackagesColumn(QListWidget *new_list_widget) :
    QObject(),
    checked_packages(0),
    list_widget(new_list_widget)
{}


template<typename T>
QStringList PackagesColumn::collectCheckedPackages()
{
    QStringList checked_packages = QStringList();
    for(int i = 0; i < list_widget->count(); ++i)
    {
        T* item = dynamic_cast<T*>(list_widget->item(i));

        if (item->checkState() == Qt::Checked)
            checked_packages.append(item->getName());
    }

    return checked_packages;
}


template<typename T>
void PackagesColumn::fill()
{
    QStringList pak_packages = getPackagesList<T>();
    QStringList::iterator it = pak_packages.begin();
    int i = 0;

    for(; it != pak_packages.end(); it++)
    {
        list_widget->insertItem(i, new T (*it));
        i++;
    }

    list_widget->update();
}


void PackagesColumn::clear()
{
    checked_packages = 0;
    list_widget->clear();
    list_widget->update();
}

template<typename T>
void PackagesColumn::update(int exit_code, QProcess::ExitStatus exit_status,
                               const QString &warning_title, const QString &action_verb)
{
    Q_UNUSED(exit_code)

    if (exit_status == QProcess::ExitStatus::CrashExit)
    {
        QMessageBox::warning(new QWidget, warning_title,
                             tr("Packages couln't be %1\n"
                                "Do you want to see logs?").arg(action_verb),
                             QMessageBox::Yes | QMessageBox::Cancel);
        return;
    }

    list_widget->clear();
    fill<T>();
    list_widget->update();
}


void PackagesColumn::sort(bool is_sorted)
{
    if (is_sorted)
        list_widget->sortItems(Qt::DescendingOrder);
    else
        list_widget->sortItems(Qt::AscendingOrder);

    list_widget->update();
}


void PackagesColumn::updateCheckedPackagesCounter(QListWidgetItem *package_item)
{
    if (package_item->checkState() == Qt::Checked)
        checked_packages++;
    else
        checked_packages--;

    emit checkedPackagesCounterChanged(checked_packages > 0);
}


template<typename T>
QStringList PackagesColumn::getPackagesList()
{
    QScopedPointer<T> command_parser(new T);
    return command_parser.data()->retrieveInfo();
}
