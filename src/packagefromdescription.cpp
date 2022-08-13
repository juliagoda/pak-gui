#include "packagefromdescription.h"

#include <QTextStream>
#include <QDebug>

#include "defs.h"


PackageFromDescription::PackageFromDescription(QString& package_content) :
    Package(package_content)
{
    updateData(package_content);
}


void PackageFromDescription::updateData(QString& packageContent)
{
    QStringList lines = packageContent.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

    if (lines.count() == 0)
        return;

    int name_separator_index = lines.at(PACKAGE_NAME_LINE).indexOf(": ") + 1;
    setName(lines.at(PACKAGE_NAME_LINE).mid(name_separator_index));

    int version_separator_index = lines.at(PACKAGE_VERSION_LINE).indexOf(": ") + 1;
    setVersion(lines.at(PACKAGE_VERSION_LINE).mid(version_separator_index));

    int description_separator_index = lines.at(PACKAGE_DESCRIPTION_LINE).indexOf(": ") + 1;
    setDescription(lines.at(PACKAGE_DESCRIPTION_LINE).mid(description_separator_index));

    int dependencies_separator_index = lines.at(PACKAGE_DEPENDENCIES_LINE).indexOf(": ") + 1;
    setDependencies(lines.at(PACKAGE_DEPENDENCIES_LINE).mid(dependencies_separator_index));
}
