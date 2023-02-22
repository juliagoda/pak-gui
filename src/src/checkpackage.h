#pragma once

#include "package.h"


class CheckPackage : public Package
{
public:
    explicit CheckPackage(const QString& package_content, Package::Source new_source);
    CheckPackage(CheckPackage& check_package);
    ~CheckPackage() override = default;

private:
    virtual void updateData(const QString& packageContent, int name_line, int version_line) override;
};
