#include "sorter.h"

#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <algorithm>

Sorter::Sorter(QListWidget* list_widgets) :
    list_widget(list_widgets),
    untouched_list_widget(new QListWidget, &QObject::deleteLater)
{

}


void Sorter::reverseSort()
{
    QtConcurrent::run(this, &Sorter::sortReverse);
}


void Sorter::sortReverse()
{
    auto widgets_list = list_widget->findItems("*", Qt::MatchWildcard);

    clear();

    QList<QListWidgetItem*>::reverse_iterator widgets_it;
    for(widgets_it = widgets_list.rbegin(); widgets_it != widgets_list.rend(); widgets_it++)
    {
        list_widget->addItem(*widgets_it);
    }
}


void Sorter::sortByText(const QString& text)
{
    auto widgets_list = untouched_list_widget->findItems(QString(" ") + text, Qt::MatchStartsWith);

    clear();

    int i = 0;
    QList<QListWidgetItem*>::iterator widgets_it;
    for(widgets_it = widgets_list.begin(); widgets_it != widgets_list.end(); widgets_it++)
    {
        list_widget->addItem(new QListWidgetItem(**widgets_it));
        i++;
    }
}


void Sorter::clear()
{
    while(list_widget->count() > 0)
    {
        if (list_widget->item(0))
            list_widget->takeItem(0);
    }
}


void Sorter::updateOriginalList(int index, Package* package)
{
    untouched_list_widget->insertItem(index, package);
}


void Sorter::resetOriginalList()
{
    untouched_list_widget->clear();
}
