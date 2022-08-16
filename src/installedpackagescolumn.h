#pragma once

#include "packagescolumn.h"

#include <QStringList>

class InstalledPackagesColumn : public PackagesColumn
{
public:
    InstalledPackagesColumn();
    void fill(QListWidget* list_widget) override;

protected:
    QStringList getPackagesList() override;

private:
    QStringList pak_packages;
};


