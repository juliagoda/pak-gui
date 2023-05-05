#pragma once

#include "sorter.h"

#include <QLineEdit>
#include <QListWidget>
#include <QProcess>
#include <QStringList>
#include <QMessageBox>
#include <QtConcurrent>


class PackagesColumn : public QObject
{
    Q_OBJECT

public:
    PackagesColumn(QListWidget* new_list_widget,
                   QLineEdit* new_search_lineedit,
                   QCheckBox* new_reverse_sort_checkbox,
                   QWidget* new_parent);
    ~PackagesColumn() override = default;

    virtual void fill();
    virtual void clear();

    QList<Package*> getCheckedPackagesList() const;
    QStringList getCheckedPackagesStringList();
    uint getAurPackagesCount() const;

public Q_SLOTS:
    virtual void update(int exit_code,
                        QProcess::ExitStatus exit_status,
                        const QString& warning_title,
                        const QString& action_verb);

    virtual void sort(bool is_sorted);
    virtual void countCheckedPackages(QListWidgetItem* item);

signals:
    void checkedPackagesCounterChanged(bool has_checked_buttons);

protected:
    void addCheckedPackage(Package* package);
    void removeUncheckedPackage(Package* package);

    int checked_packages;
    uint aur_checked_packages;
    QListWidget* list_widget;
    QLineEdit* search_lineedit;
    QSharedPointer<Sorter> packages_sorter;
    QWidget* parent;
    QList<Package*> checked_packages_list;
};

