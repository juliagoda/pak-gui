#pragma once

#include "packagescolumn.h"

#include <QStringList>
#include <QPointer>
#include <QListWidget>
#include <QTextBrowser>


class AvailablePackagesColumn : public PackagesColumn
{
    Q_OBJECT

public:
    AvailablePackagesColumn(QListWidget* new_list_widget, QTextBrowser* new_packages_installation_textarea);
    void update(int exit_code, QProcess::ExitStatus exit_status) override;
    QStringList collectCheckedPackages() override;
    void fill() override;

public Q_SLOTS:
    void updateCheckedPackagesCounter(QListWidgetItem* package_item);
    void sort(bool is_sorted) override;

signals:
    void checkedPackagesCounterChanged(bool has_checked_buttons);

protected:
    QStringList getPackagesList() override;

private:
    int checked_packages;
    QListWidget* list_widget;
    QTextBrowser* packages_installation_textarea;
    QStringList pak_packages;
};

