#pragma once

#include <QListWidget>
#include <QStringList>

class PackagesColumn
{
public:
    virtual ~PackagesColumn() = default;
    virtual void fill(QListWidget* list_widget) =  0;

protected:
    virtual QStringList getPackagesList() = 0;
};

