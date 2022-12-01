#include "sipackage.h"
#include "defs.h"


SiPackage::SiPackage(QString& package_content) :
    Package(package_content),
    repo()
{
    updateData(package_content, PACKAGE_SI_NAME_LINE, PACKAGE_SI_VERSION_LINE);
    setText(getName().trimmed() + "-" + getVersion().trimmed() + " [" + getRepo().trimmed() + "]");
    setFlags(flags() | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Unchecked);
}


SiPackage::SiPackage(SiPackage& si_package) :
    Package(si_package),
    repo()
{
    setName(si_package.getName());
    setVersion(si_package.getVersion());
    setRepo(si_package.getRepo());
    setText(getName().trimmed() + "-" + getVersion().trimmed() + " [" + getRepo().trimmed() + "]");
    setFlags(flags() | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Unchecked);
    setToolTip(si_package.toolTip());
}


void SiPackage::updateData(QString& packageContent, int name_line, int version_line)
{
    Package::updateData(packageContent, name_line, version_line);
    QStringList lines = packageContent.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

    if (lines.count() == 0)
        return;

    int repo_separator_index = lines.at(PACKAGE_SI_REPO_NAME).indexOf(": ") + 1;
    setRepo(lines.at(PACKAGE_SI_REPO_NAME).mid(repo_separator_index));

    int name_separator_index = lines.at(PACKAGE_SI_NAME_LINE).indexOf(": ") + 1;
    setName(lines.at(PACKAGE_SI_NAME_LINE).mid(name_separator_index));

    int version_separator_index = lines.at(PACKAGE_SI_VERSION_LINE).indexOf(": ") + 1;
    setVersion(lines.at(PACKAGE_SI_VERSION_LINE).mid(version_separator_index));
}
