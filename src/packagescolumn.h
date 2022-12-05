#pragma once

#include "qlineedit.h"
#include "qobjectdefs.h"
#include "sorter.h"

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
        parent(new_parent)
    {

    };

    virtual QStringList collectCheckedPackages() { return QStringList(); };
    virtual void fill()
    {

    };
    virtual void clear()
    {
        checked_packages = 0;
        list_widget->clear();
        list_widget->update();
    };

public Q_SLOTS:
    virtual void update(int exit_code, QProcess::ExitStatus exit_status,
                const QString& warning_title, const QString& action_verb)
    {
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

    virtual void updateCheckedPackagesCounter(QListWidgetItem* package_item)
    {
        if (package_item->checkState() == Qt::Checked)
            checked_packages++;
        else
            checked_packages--;

        emit checkedPackagesCounterChanged(checked_packages > 0);
    }

signals:
    void checkedPackagesCounterChanged(bool has_checked_buttons);

protected:
    virtual QStringList getPackagesList() { return QStringList(); };

    int checked_packages;
    QListWidget* list_widget;
    QLineEdit* search_lineedit;
    QSharedPointer<Sorter> packages_sorter;
    QWidget* parent;
};

