#pragma once

#include "packagescolumn.h"

#include <QStringList>
#include <QPointer>
#include <QListWidget>


class AvailablePackagesColumn : public PackagesColumn
{
    Q_OBJECT

public:
    AvailablePackagesColumn(QListWidget* new_list_widget);
    void update(int exit_code, QProcess::ExitStatus exit_status) override;
    QStringList collectCheckedPackages() override;
    void fill() override;

public Q_SLOTS:
    void updateCheckedPackagesCounter(QListWidgetItem* package_item);

signals:
    void checkedPackagesCounterChanged(bool has_checked_buttons);

protected:
    QStringList getPackagesList() override;

private:
    QStringList pak_packages;
    int checked_packages;
    QListWidget* list_widget;
};

