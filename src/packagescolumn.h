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

    virtual void update(int exit_code, QProcess::ExitStatus exit_status) {};
    virtual QStringList collectCheckedPackages() { return QStringList(); };
    virtual void fill() {};

protected:
    virtual QStringList getPackagesList() { return QStringList(); };
};

