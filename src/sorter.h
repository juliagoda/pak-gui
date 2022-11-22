#pragma once

#include "package.h"

#include <QList>
#include <QListWidgetItem>

class Sorter : public QObject
{

    Q_OBJECT

public:
    Sorter(QListWidget* list_widgets);

    void reverseSort();
    void updateOriginalList(int index, Package* package);
    void resetOriginalList();

public Q_SLOTS:
    void sortReverse();
    void sortByText(const QString& text);

private:
    void clear();

    QListWidget* list_widget;
    QSharedPointer<QListWidget> untouched_list_widget;
};

