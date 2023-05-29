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
#include <iterator>

QMutex Sorter::mutex;

Sorter::Sorter(QListWidget* list_widgets,
               QCheckBox* new_reverse_sort_checkbox) :
    list_widget(list_widgets),
    reverse_sort_checkbox(new_reverse_sort_checkbox),
    untouched_list_widget()
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


template<typename T>
void Sorter::sortPackagesByText(const QString &text, T emptyPackage)
{
    Q_UNUSED(emptyPackage) // we have errors without T as argument

    if (untouched_list_widget.empty())
        fillUntouchedList<T>();

    clear();
    QVector<QListWidgetItem*>::reverse_iterator widgets_reversed_it;

    if (reverse_sort_checkbox->checkState() == Qt::Checked)
    {
        for (widgets_reversed_it = untouched_list_widget.rbegin(); widgets_reversed_it != untouched_list_widget.rend(); widgets_reversed_it++)
        {
            if (!(*widgets_reversed_it)->text().startsWith(text))
                continue;

            T* item = dynamic_cast<T*>(*widgets_reversed_it);
            list_widget->addItem(new T(*item));
        }

        showInfo();
        return;
    }

    QVector<QListWidgetItem*>::iterator widgets_it;
    for (widgets_it = untouched_list_widget.begin(); widgets_it != untouched_list_widget.end(); widgets_it++)
    {
        if (!(*widgets_it)->text().startsWith(text))
            continue;

        T* item = dynamic_cast<T*>(*widgets_it);
        list_widget->addItem(new T(*item));
    }

    showInfo();
}


void Sorter::setCheckStateForUnsortedList(QListWidgetItem* item)
{
    if (untouched_list_widget.count() == 0)
        return;

    Package* package = dynamic_cast<Package*>(item);
    untouched_list_widget.at(package->getNo() - 1)->setCheckState(item->checkState());
}


void Sorter::showInfo()
{
    if (!Settings::records()->showDebug())
        return;

    auto all_items = list_widget->findItems("*", Qt::MatchWildcard);
    Logger::logger()->logDebug(QStringLiteral("Count of sorted packages: %1").arg(all_items.count()));
}


template <typename T>
void Sorter::fillUntouchedList()
{
    auto widgets_list = list_widget->findItems("*", Qt::MatchWildcard);
    untouched_list_widget.reserve(widgets_list.count());
    std::transform(widgets_list.begin(), widgets_list.end(), std::back_inserter(untouched_list_widget),
                   [](QListWidgetItem* item) { return dynamic_cast<T*>(item); });
}


void Sorter::clear()
{
    while (list_widget->count() > 0)
    {
        if (list_widget->item(0))
            list_widget->takeItem(0);
    }
}


void Sorter::resetOriginalList()
{
    if (untouched_list_widget.count() == 0)
        return;

    untouched_list_widget.clear();
}


// forward declarations

template void Sorter::sortPackagesByText(const QString& text, CheckPackage);
template void Sorter::sortPackagesByText(const QString& text, SiPackage);
template void Sorter::sortPackagesByText(const QString& text, QiPackage);
