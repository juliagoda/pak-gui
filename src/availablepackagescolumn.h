#pragma once

#include "packagescolumn.h"

#include <QStringList>

class AvailablePackagesColumn : public PackagesColumn
{
public:
    AvailablePackagesColumn();
    void fill(QListWidget* list_widget) override;

protected:
    QStringList getPackagesList() override;

private:
    QStringList pak_packages;
};

