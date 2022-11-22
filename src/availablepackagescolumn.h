#pragma once

#include "packagescolumn.h"

#include <QStringList>
#include <QPointer>
#include <QListWidget>


class AvailablePackagesColumn : public PackagesColumn
{
    Q_OBJECT

public:
    AvailablePackagesColumn(QListWidget* new_list_widget, QLineEdit* new_search_lineedit);
    QStringList collectCheckedPackages() override;
    void fill() override;

protected:
    QStringList getPackagesList() override;
};

