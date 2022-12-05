#pragma once

#include "packagescolumn.h"

#include <QStringList>


class UpdatedPackagesColumn : public PackagesColumn
{
    Q_OBJECT

public:
    UpdatedPackagesColumn(QListWidget* new_list_widget, QLineEdit* new_search_lineedit, QWidget* new_parent);
    QStringList collectCheckedPackages() override;
    void fill() override;

public Q_SLOTS:
    void toggleAllPackages(bool is_all_checked);

protected:
    QStringList getPackagesList() override;

signals:
    void startOtherThreads();
    void currentPackagesCountChanged(int new_current_packages_count);

private:
    void updatePackagesCount(int new_current_packages_count);

    int current_packages_count;
};

