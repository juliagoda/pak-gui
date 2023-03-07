#pragma once

#include "package.h"

#include <QObject>
#include <QString>

class SiPackage : public Package
{
public:
    SiPackage(const QString& package_content);
    SiPackage(SiPackage& check_package);
    ~SiPackage() override = default;

    const QString& getRepo() const { return repo; };

private:
    void updateData(const QString& package_content, int name_line, int version_line) override;
    void setRepo(const QString& new_repo) { repo = new_repo; };
    void buildTooltipsLinesMap() override;

    QString repo;
};
