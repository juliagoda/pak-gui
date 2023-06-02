#pragma once

#include "packagescolumn.h"
#include "process.h"

#include <QStringList>
#include <QHash>


class UpdatedPackagesColumn : public PackagesColumn
{
    Q_OBJECT

public:
    UpdatedPackagesColumn(QListWidget* new_list_widget,
                          QLineEdit* new_search_lineedit,
                          QCheckBox* new_reverse_sort_checkbox,
                          QWidget* new_parent);
    uint getCurrentPackagesCount() const;
    void fill() override;
    void clearForSort();

public Q_SLOTS:
    void toggleAllPackages(bool is_all_checked);
    void prepareBeforeProcessRun();

protected:
    virtual QHash<QString, Package::Source> getPackagesList();

signals:
    void currentPackagesCountChanged(int new_current_packages_count);
    void chosenUpdateAll();
    void chosenUncheckSidePackages();
    void preparedList(QStringList packages, Process::Task, uint aur_checked_packages);

private:
    void updatePackagesCount(uint new_current_packages_count);

    template<int> void runAfterChoice();

    uint current_packages_count;
    QWidget* parent;
};

