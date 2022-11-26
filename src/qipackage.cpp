#include "qipackage.h"
#include "defs.h"
#include "settings.h"

#include <QTextStream>


QiPackage::QiPackage(QString& package_content) :
    Package(package_content)
{
    updateData(package_content, PACKAGE_QI_NAME_LINE, PACKAGE_QI_VERSION_LINE);
    setText(getName().trimmed() + "-" + getVersion().trimmed());
    setFlags(flags() | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Unchecked);
}


QiPackage::QiPackage(QiPackage& qi_package) :
    Package(qi_package)
{
    setName(qi_package.getName());
    setVersion(qi_package.getVersion());
    setText(getName().trimmed() + "-" + getVersion().trimmed());
    setFlags(flags() | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Unchecked);
    setToolTip(qi_package.toolTip());
}
