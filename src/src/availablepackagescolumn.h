#pragma once

#include "packagescolumn.h"

#include <QStringList>
#include <QPointer>
#include <QListWidget>


class AvailablePackagesColumn : public PackagesColumn
{
    Q_OBJECT

public:
    AvailablePackagesColumn(QListWidget* new_list_widget,
                            QLineEdit* new_search_lineedit,
                            QCheckBox* new_reverse_sort_checkbox,
                            QWidget* new_parent);
    ~AvailablePackagesColumn() override = default;

    void fill() override;
    void clearForSort();

protected:
    virtual QStringList getPackagesList();
};

