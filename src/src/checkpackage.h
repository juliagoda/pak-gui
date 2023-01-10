#pragma once

#include "package.h"

class CheckPackage : public Package
{
public:
    CheckPackage(const QString& package_content, Package::Source new_source);
    CheckPackage(CheckPackage& check_package);

private:
    virtual void updateData(QString& packageContent, int name_line, int version_line) override;
};
