#pragma once

#include "package.h"


class CheckPackage : public Package
{
public:
    explicit CheckPackage(QString package_content, Package::Source new_source);
    CheckPackage(CheckPackage& check_package);
    virtual ~CheckPackage() override = default;

private:
    virtual void updateData(const QString& package_content, int name_line, int version_line) override;
};
