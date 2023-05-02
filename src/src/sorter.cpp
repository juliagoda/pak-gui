#include "sorter.h"

#include "logger.h"
#include "qnamespace.h"
#include "settings.h"
#include "checkpackage.h"
#include "sipackage.h"
#include "qipackage.h"

#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <algorithm>

QMutex Sorter::mutex;

Sorter::Sorter(QListWidget* list_widgets,
               QCheckBox* new_reverse_sort_checkbox) :
    list_widget(list_widgets),
    reverse_sort_checkbox(new_reverse_sort_checkbox),
    untouched_list_widget(new QListWidget)
{
   // ...
}


void Sorter::sortReverse()
{
    mutex.tryLock();
    auto widgets_list = list_widget->findItems("*", Qt::MatchWildcard);

    clear();

    QList<QListWidgetItem*>::reverse_iterator widgets_it;
    for (widgets_it = widgets_list.rbegin(); widgets_it != widgets_list.rend(); widgets_it++)
    {
        list_widget->addItem(*widgets_it);
    }

    mutex.unlock();
    if (!Settings::records()->showDebug())
        return;

    auto all_items = list_widget->findItems("*", Qt::MatchWildcard);
    QList<QListWidgetItem*>::iterator first_list_iterator = all_items.begin();
    QList<QListWidgetItem*>::iterator last_list_iterator = all_items.end();
    Logger::logger()->logDebug(QStringLiteral("Reverse sorting - now first package is \"%1\" and last one \"%2\"").arg((*first_list_iterator)->text(), (*last_list_iterator)->text()));
}


void Sorter::sortPackagesToUpdateByText(const QString &text)
{
    auto widgets_list = untouched_list_widget->findItems(text, Qt::MatchStartsWith);
    clear();
    QList<QListWidgetItem*>::iterator widgets_it;

    for(widgets_it = widgets_list.begin(); widgets_it != widgets_list.end(); widgets_it++)
    {
        CheckPackage* item = dynamic_cast<CheckPackage*>(*widgets_it);
        list_widget->addItem(new CheckPackage(*item));
    }

    showInfo();
}


void Sorter::sortAvailablePackagesByText(const QString &text)
{
    auto widgets_list = untouched_list_widget->findItems(text, Qt::MatchStartsWith);
    clear();
    QList<QListWidgetItem*>::iterator widgets_it;

    for(widgets_it = widgets_list.begin(); widgets_it != widgets_list.end(); widgets_it++)
    {
        SiPackage* item = dynamic_cast<SiPackage*>(*widgets_it);
        list_widget->addItem(new SiPackage(*item));
    }

    if (reverse_sort_checkbox->checkState() == Qt::Checked)
        sortReverse();

    showInfo();
}


void Sorter::sortInstalledPackagesByText(const QString &text)
{
    auto widgets_list = untouched_list_widget->findItems(text, Qt::MatchStartsWith);
    clear();
    QList<QListWidgetItem*>::iterator widgets_it;

    for(widgets_it = widgets_list.begin(); widgets_it != widgets_list.end(); widgets_it++)
    {
        QiPackage* item = dynamic_cast<QiPackage*>(*widgets_it);
        list_widget->addItem(new QiPackage(*item));
    }

    if (reverse_sort_checkbox->checkState() == Qt::Checked)
        sortReverse();

    showInfo();
}


void Sorter::setCheckStateForUnsortedList(QListWidgetItem* item)
{
    if (untouched_list_widget.isNull() || untouched_list_widget->count() == 0)
        return;

    Package* package = dynamic_cast<Package*>(item);
    untouched_list_widget->item(package->getNo() - 1)->setCheckState(item->checkState());
}


void Sorter::showInfo()
{
    if (!Settings::records()->showDebug())
        return;

    auto all_items = list_widget->findItems("*", Qt::MatchWildcard);
    Logger::logger()->logDebug(QStringLiteral("Count of sorted packages: %1").arg(all_items.count()));
}


void Sorter::clear()
{
    while (list_widget->count() > 0)
    {
        if (list_widget->item(0))
            list_widget->takeItem(0);
    }
}


void Sorter::updateOriginalList(int index, Package* package)
{
    if (untouched_list_widget.isNull())
        untouched_list_widget.reset(new QListWidget);

    untouched_list_widget->insertItem(index, package);
}


void Sorter::resetOriginalList()
{
    if (untouched_list_widget.isNull() || untouched_list_widget->count() == 0)
        return;

    untouched_list_widget.clear();
}
