#pragma once

#include "qobjectdefs.h"
#include <QListWidget>
#include <QStringList>

class PackagesColumn : public QObject
{
    Q_OBJECT

public:
    PackagesColumn() :
        QObject()
    {};
    virtual void fill() {};

protected:
    virtual QStringList getPackagesList() { return QStringList(); };
};

