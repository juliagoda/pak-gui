#pragma once

#include "package.h"

class CheckPackage : public Package
{
public:
    CheckPackage(QString& package_content);

private:
    virtual void updateData(QString &packageContent) override;
};

