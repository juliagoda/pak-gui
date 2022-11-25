#pragma once

#include "package.h"

class CheckPackage : public Package
{
public:
    CheckPackage(QString& package_content);
    CheckPackage(CheckPackage& check_package);

private:
    virtual void updateData(QString &packageContent) override;
};

