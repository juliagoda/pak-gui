#pragma once

#include "packagescolumn.h"

#include <QStringList>

class UpdatedPackagesColumn : public PackagesColumn
{
public:
    UpdatedPackagesColumn();
    void fill(QListWidget* list_widget) override;

protected:
    QStringList getPackagesList() override;

private:
    QStringList pak_packages;
};

