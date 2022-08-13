#pragma once

#include "package.h"

#include <QObject>
#include <QString>

class PackageFromDescription : public Package
{
public:
    PackageFromDescription(QString& package_content);

private:
    virtual void updateData(QString &packageContent) override;
};

