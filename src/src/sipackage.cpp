#include "sipackage.h"

#include "defs.h"
#include "qnamespace.h"


SiPackage::SiPackage(const QString& package_content) :
    Package(package_content, Package::Source::Unknown),
    repo()
{
    updateData(package_content, Constants::packageSiNameLine(), Constants::packageSiVersionLine());
    setText(getName().trimmed() + "-" + getVersion().trimmed() + " [" + getRepo().trimmed() + "]");
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Unchecked);
}


SiPackage::SiPackage(SiPackage& si_package) :
    Package(si_package),
    repo()
{
    setName(si_package.getName());
    setNo(si_package.getNo());
    setVersion(si_package.getVersion());
    setRepo(si_package.getRepo());
    setText(getName().trimmed() + "-" + getVersion().trimmed() + " [" + getRepo().trimmed() + "]");
    setFlags(si_package.flags());
    setCheckState(si_package.checkState());
    setToolTip(si_package.toolTip());
}


void SiPackage::updateData(const QString& package_content, int name_line, int version_line)
{
    Package::updateData(package_content, name_line, version_line);
    QStringList lines = package_content.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

    if (lines.count() == 0)
        return;

    if (!validate(lines, Constants::packageSiRepoName() + 1, QString("updateData()")))
        return;

    int repo_separator_index = lines.at(Constants::packageSiRepoName()).indexOf(": ") + 1;
    setRepo(lines.at(Constants::packageSiRepoName()).mid(repo_separator_index));

    if (!validate(lines, Constants::packageSiNameLine() + 1, QString("updateData()")))
        return;

    int name_separator_index = lines.at(Constants::packageSiNameLine()).indexOf(": ") + 1;
    setName(lines.at(Constants::packageSiNameLine()).mid(name_separator_index));

    if (!validate(lines, Constants::packageSiVersionLine() + 1, QString("updateData()")))
        return;

    int version_separator_index = lines.at(Constants::packageSiVersionLine()).indexOf(": ") + 1;
    setVersion(lines.at(Constants::packageSiVersionLine()).mid(version_separator_index));
}
