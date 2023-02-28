#include "qipackage.h"

#include "defs.h"

#include <QTextStream>


QiPackage::QiPackage(const QString& package_content) :
    Package(package_content, Package::Source::Unknown)
{
    updateData(package_content, Constants::packageQiNameLine(), Constants::packageQiVersionLine());
    setText(getName().trimmed() + "-" + getVersion().trimmed());
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Unchecked);
}


QiPackage::QiPackage(QiPackage& qi_package) :
    Package(qi_package)
{
    setName(qi_package.getName());
    setNo(qi_package.getNo());
    setVersion(qi_package.getVersion());
    setText(getName().trimmed() + "-" + getVersion().trimmed());
    setFlags(qi_package.flags());
    setCheckState(qi_package.checkState());
    setToolTip(qi_package.toolTip());
}
