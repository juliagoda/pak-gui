#pragma once

#include "package.h"

#include <QList>
#include <QListWidgetItem>

class Sorter : public QObject
{
    Q_OBJECT

public:
    Sorter(QListWidget* list_widgets);
    ~Sorter() override = default;

    void reverseSort();
    void updateOriginalList(int index, Package* package);
    void resetOriginalList();
    QListWidget* listWidget() { return untouched_list_widget.get(); }

public Q_SLOTS:
    void sortReverse();
    void sortPackagesToUpdateByText(const QString& text);
    void sortAvailablePackagesByText(const QString& text);
    void sortInstalledPackagesByText(const QString& text);

private:
    void clear();
    void showInfo();

    QListWidget* list_widget;
    QSharedPointer<QListWidget> untouched_list_widget;
};

