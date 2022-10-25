#pragma once

#include "qobjectdefs.h"

#include <QListWidget>
#include <QProcess>
#include <QStringList>
#include <QMessageBox>

class PackagesColumn : public QObject
{
    Q_OBJECT

public:
    PackagesColumn(QListWidget* new_list_widget) :
        QObject(),
        checked_packages(0),
        list_widget(new_list_widget)
    {};

    virtual QStringList collectCheckedPackages() { return QStringList(); };
    virtual void fill() {};
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
            QMessageBox::warning(new QWidget, warning_title,
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
        if (is_sorted)
            list_widget->sortItems(Qt::DescendingOrder);
        else
            list_widget->sortItems(Qt::AscendingOrder);

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
};

