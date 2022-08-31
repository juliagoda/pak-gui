#pragma once

#include "qobjectdefs.h"

#include <QListWidget>
#include <QProcess>
#include <QStringList>


class PackagesColumn : public QObject
{
    Q_OBJECT

public:
    PackagesColumn() :
        QObject()
    {};

    virtual void update(int exit_code, QProcess::ExitStatus exit_status) { Q_UNUSED(exit_code) Q_UNUSED(exit_status) };
    virtual QStringList collectCheckedPackages() { return QStringList(); };
    virtual void fill() {};
    virtual void sort(bool is_sorted) { Q_UNUSED(is_sorted) };

protected:
    virtual QStringList getPackagesList() { return QStringList(); };
};

