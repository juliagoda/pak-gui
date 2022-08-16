#pragma once

#include "packagescolumn.h"

#include <QStringList>

class InstalledPackagesColumn : public PackagesColumn
{
    Q_OBJECT

public:
    InstalledPackagesColumn(QListWidget* new_list_widget);
    void fill() override;

public Q_SLOTS:
    void updateCheckedPackagesCounter(QListWidgetItem* package_item);

signals:
    void checkedPackagesCounterChanged(bool has_checked_buttons);

protected:
    QStringList getPackagesList() override;

private:
    QStringList pak_packages;
    int checked_packages;
    QListWidget* list_widget;
};


