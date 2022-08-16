#pragma once

#include "package.h"

#include <QObject>
#include <QString>

class QiPackage : public Package
{
public:
    QiPackage(QString& package_content);

private:
    virtual void updateData(QString &packageContent) override;
};

