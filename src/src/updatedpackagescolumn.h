#pragma once

#include "packagescolumn.h"
#include "process.h"

#include <QStringList>
#include <QHash>


class UpdatedPackagesColumn : public PackagesColumn
{
    Q_OBJECT

public:
    UpdatedPackagesColumn(QListWidget* new_list_widget, QLineEdit* new_search_lineedit, QWidget* new_parent);
    uint getCurrentPackagesCount() const;
    void fill() override;

public Q_SLOTS:
    void toggleAllPackages(bool is_all_checked);
    void prepareBeforeProcessRun();

protected:
    virtual QHash<QString, Package::Source> getPackagesList();

signals:
    void currentPackagesCountChanged(int new_current_packages_count);
    void chosenUpdateAll();
    void chosenUncheckSidePackages();
    void preparedList(QStringList packages, Process::Task);

private:
    void updatePackagesCount(uint new_current_packages_count);

    uint current_packages_count;
    QWidget* parent;
};

