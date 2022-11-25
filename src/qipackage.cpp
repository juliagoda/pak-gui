#include "qipackage.h"
#include "logger.h"
#include "defs.h"

#include <QTextStream>


QiPackage::QiPackage(QString& package_content) :
    Package(package_content)
{
    updateData(package_content);
    setText(getName() + "-" + getVersion());
    setFlags(flags() | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Unchecked);
    setToolTip(getDescription() + QString("\n\n") + QString("dependencies: ") + getDependencies());
    Logger::logger()->logDebug(QStringLiteral("tooltip on installed package looks like this now:\n\"%1\"").arg(toolTip()));
}


void QiPackage::updateData(QString& packageContent)
{
    QStringList lines = packageContent.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

    if (lines.count() == 0)
        return;

    int name_separator_index = lines.at(PACKAGE_QI_NAME_LINE).indexOf(": ") + 1;
    setName(lines.at(PACKAGE_QI_NAME_LINE).mid(name_separator_index));

    int version_separator_index = lines.at(PACKAGE_QI_VERSION_LINE).indexOf(": ") + 1;
    setVersion(lines.at(PACKAGE_QI_VERSION_LINE).mid(version_separator_index));

    int description_separator_index = lines.at(PACKAGE_QI_DESCRIPTION_LINE).indexOf(": ") + 1;
    setDescription(lines.at(PACKAGE_QI_DESCRIPTION_LINE).mid(description_separator_index));

    int dependencies_separator_index = lines.at(PACKAGE_QI_DEPENDENCIES_LINE).indexOf(": ") + 1;
    setDependencies(lines.at(PACKAGE_QI_DEPENDENCIES_LINE).mid(dependencies_separator_index));
}
