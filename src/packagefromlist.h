#pragma once

#include "package.h"

class PackageFromList : public Package
{
public:
    PackageFromList(QString& package_content);

private:
    virtual void updateData(QString &packageContent) override;
};

