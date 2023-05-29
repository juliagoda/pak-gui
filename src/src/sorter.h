#pragma once

#include "package.h"

#include <QList>
#include <QListWidgetItem>
#include <QMutex>
#include <QCheckBox>

class Sorter : public QObject
{
    Q_OBJECT

public:
    Sorter(QListWidget* list_widgets,
           QCheckBox* new_reverse_sort_checkbox);
    ~Sorter() override = default;

    void resetOriginalList();
    QVector<QListWidgetItem*> listWidget() { return untouched_list_widget; }

    template <typename T>
    void sortPackagesByText(const QString& text, T emptyPackage);

public Q_SLOTS:
    void sortReverse();
    void setCheckStateForUnsortedList(QListWidgetItem* item);

private:
    void clear();
    void showInfo();
    template <typename T>
    void fillUntouchedList();

    QListWidget* list_widget;
    QCheckBox* reverse_sort_checkbox;
    QVector<QListWidgetItem*> untouched_list_widget;
    static QMutex mutex;
};

