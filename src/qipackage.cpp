#include "qipackage.h"
#include "defs.h"

#include <QTextStream>


QiPackage::QiPackage(QString& package_content) :
    Package(package_content, Package::Source::Unknown)
{
    updateData(package_content, PACKAGE_QI_NAME_LINE, PACKAGE_QI_VERSION_LINE);
    setText(getName().trimmed() + "-" + getVersion().trimmed());
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Unchecked);
}


QiPackage::QiPackage(QiPackage& qi_package) :
    Package(qi_package)
{
    setName(qi_package.getName());
    setVersion(qi_package.getVersion());
    setText(getName().trimmed() + "-" + getVersion().trimmed());
    setFlags(qi_package.flags());
    setCheckState(qi_package.checkState());
    setToolTip(qi_package.toolTip());
}
