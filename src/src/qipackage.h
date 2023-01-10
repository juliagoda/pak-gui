#pragma once

#include "package.h"

#include <QObject>
#include <QString>

class QiPackage : public Package
{
public:
    QiPackage(QString& package_content);
    QiPackage(QiPackage& check_package);
};

