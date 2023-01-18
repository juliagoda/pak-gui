#pragma once

#include "packagescolumn.h"

#include <QStringList>


class InstalledPackagesColumn : public PackagesColumn
{
    Q_OBJECT

public:
    InstalledPackagesColumn(QListWidget* new_list_widget, QLineEdit* new_search_lineedit, QWidget* new_parent);
    void fill() override;

protected:
    virtual QStringList getPackagesList();
};


