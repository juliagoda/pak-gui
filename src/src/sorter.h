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

    void updateOriginalList(int index, Package* package);
    void resetOriginalList();
    QListWidget* listWidget() { return untouched_list_widget.get(); }

public Q_SLOTS:
    void sortReverse();
    void sortPackagesToUpdateByText(const QString& text);
    void sortAvailablePackagesByText(const QString& text);
    void sortInstalledPackagesByText(const QString& text);
    void setCheckStateForUnsortedList(QListWidgetItem* item);

private:
    void clear();
    void showInfo();

    QListWidget* list_widget;
    QCheckBox* reverse_sort_checkbox;
    QSharedPointer<QListWidget> untouched_list_widget;
    static QMutex mutex;
};

