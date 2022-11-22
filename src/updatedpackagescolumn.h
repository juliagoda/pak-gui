#pragma once

#include "packagescolumn.h"

#include <QStringList>


class UpdatedPackagesColumn : public PackagesColumn
{
    Q_OBJECT

public:
    UpdatedPackagesColumn(QListWidget* new_list_widget, QLineEdit* new_search_lineedit);
    QStringList collectCheckedPackages() override;
    void fill() override;

protected:
    QStringList getPackagesList() override;
};

