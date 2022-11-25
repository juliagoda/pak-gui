#pragma once

#include "package.h"

#include <QObject>
#include <QString>

class SiPackage : public Package
{
public:
    SiPackage(QString& package_content);
    SiPackage(SiPackage& check_package);

private:
    virtual void updateData(QString &packageContent) override;
};
