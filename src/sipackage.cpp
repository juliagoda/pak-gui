#include "sipackage.h"
#include "defs.h"


SiPackage::SiPackage(QString& package_content) :
    Package(package_content)
{
    updateData(package_content);
    setText(getName() + "-" + getVersion());
    setFlags(flags() | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Unchecked);
    setToolTip(getDescription() + QString("\n\n") + QString("dependencies: ") + getDependencies());
}


SiPackage::SiPackage(SiPackage& si_package) :
    Package(si_package)
{
    setName(si_package.getName());
    setVersion(si_package.getVersion());
    setDescription(si_package.getDescription());
    setDependencies(si_package.getDependencies());
    setText(getName() + "-" + getVersion());
    setFlags(flags() | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Unchecked);
    setToolTip(getDescription() + QString("\n\n") + QString("dependencies: ") + getDependencies());
}


void SiPackage::updateData(QString& packageContent)
{
    QStringList lines = packageContent.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

    if (lines.count() == 0)
        return;

    int name_separator_index = lines.at(PACKAGE_SI_NAME_LINE).indexOf(": ") + 1;
    setName(lines.at(PACKAGE_SI_NAME_LINE).mid(name_separator_index));

    int version_separator_index = lines.at(PACKAGE_SI_VERSION_LINE).indexOf(": ") + 1;
    setVersion(lines.at(PACKAGE_SI_VERSION_LINE).mid(version_separator_index));

    int description_separator_index = lines.at(PACKAGE_SI_DESCRIPTION_LINE).indexOf(": ") + 1;
    setDescription(lines.at(PACKAGE_SI_DESCRIPTION_LINE).mid(description_separator_index));

    int dependencies_separator_index = lines.at(PACKAGE_SI_DEPENDENCIES_LINE).indexOf(": ") + 1;
    setDependencies(lines.at(PACKAGE_SI_DEPENDENCIES_LINE).mid(dependencies_separator_index));
}
