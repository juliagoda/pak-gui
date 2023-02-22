#pragma once

#include "package.h"

#include <QObject>
#include <QString>

class QiPackage : public Package
{
public:
    QiPackage(const QString& package_content);
    QiPackage(QiPackage& check_package);

    ~QiPackage() override = default;
};

