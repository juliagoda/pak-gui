#pragma once

#include "packagescolumn.h"

#include <QStringList>


class InstalledPackagesColumn : public PackagesColumn
{
    Q_OBJECT

public:
    InstalledPackagesColumn(QListWidget* new_list_widget, QLineEdit* new_search_lineedit);
    QStringList collectCheckedPackages() override;
    void fill() override;

protected:
    QStringList getPackagesList() override;
};


