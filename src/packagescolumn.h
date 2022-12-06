#pragma once

#include "qlineedit.h"
#include "qobjectdefs.h"
#include "sorter.h"
#include "logger.h"

#include <QListWidget>
#include <QProcess>
#include <QStringList>
#include <QMessageBox>


class PackagesColumn : public QObject
{
    Q_OBJECT

public:
    PackagesColumn(QListWidget* new_list_widget, QLineEdit* new_search_lineedit, QWidget* new_parent) :
        QObject(),
        checked_packages(0),
        list_widget(new_list_widget),
        search_lineedit(new_search_lineedit),
        packages_sorter(new Sorter(list_widget), &QObject::deleteLater),
        parent(new_parent),
        checked_packages_list()
    {
        QObject::connect(list_widget, &QListWidget::itemChanged, this, &PackagesColumn::countCheckedPackages);
    };

    virtual void fill()
    {

    };
    virtual void clear()
    {
        checked_packages = 0;
        list_widget->clear();
        list_widget->update();
    };

    QStringList getCheckedPackagesList() const { return checked_packages_list; }

public Q_SLOTS:
    virtual void update(int exit_code, QProcess::ExitStatus exit_status,
                        const QString& warning_title, const QString& action_verb)
    {
        Q_UNUSED(exit_code)

        if (exit_status == QProcess::ExitStatus::CrashExit)
        {
            QMessageBox::warning(parent, warning_title,
                                 tr("Packages couln't be %1\n"
                                    "Do you want to see logs?").arg(action_verb),
                                 QMessageBox::Yes | QMessageBox::Cancel);
            return;
        }

        list_widget->clear();
        fill();
        list_widget->update();
    };

    virtual void sort(bool is_sorted)
    {
        Q_UNUSED(is_sorted)
        packages_sorter->reverseSort();
        list_widget->update();
    }

    virtual void countCheckedPackages(QListWidgetItem* item)
    {
        Package* package = dynamic_cast<Package*>(item);
        if (package->checkState() == Qt::Checked)
            addCheckedPackage(package);
        else
            removeUncheckedPackage(package);

        emit checkedPackagesCounterChanged(checked_packages_list.count() > 0);
    }

signals:
    void checkedPackagesCounterChanged(bool has_checked_buttons);

protected:
    void addCheckedPackage(Package* package)
    {
        if (package->getSource() == Package::Source::AUR ||
            package->getSource() == Package::Source::POLAUR)
        {
            checked_packages_list.prepend(package->getName());
            Logger::logger()->logDebug(QStringLiteral("Added at the beginning of list package: %1").arg(package->getName()));
        }
        else
        {
            checked_packages_list.append(package->getName());
            Logger::logger()->logDebug(QStringLiteral("Added at the end of list package: %1").arg(package->getName()));
        }
    }

    void removeUncheckedPackage(Package* package)
    {
        int index = checked_packages_list.indexOf(package->getName());
        checked_packages_list.removeAt(index);
        Logger::logger()->logDebug(QStringLiteral("Removed package name from list: %1 - index: %2").arg(package->getName(), index));
    }

    int checked_packages;
    QListWidget* list_widget;
    QLineEdit* search_lineedit;
    QSharedPointer<Sorter> packages_sorter;
    QWidget* parent;
    QStringList checked_packages_list;
};

