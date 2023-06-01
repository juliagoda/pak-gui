#pragma once

#include "packagescolumn.h"

#include <QStringList>


class InstalledPackagesColumn : public PackagesColumn
{
    Q_OBJECT

public:
    InstalledPackagesColumn(QListWidget* new_list_widget,
                            QLineEdit* new_search_lineedit,
                            QCheckBox* new_reverse_sort_checkbox,
                            QWidget* new_parent);
    ~InstalledPackagesColumn() override = default;

    void fill() override;
    void clearForSort();

protected:
    virtual QStringList getPackagesList();
};


