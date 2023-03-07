#include "sipackage.h"

#include "defs.h"


SiPackage::SiPackage(const QString& package_content) :
    Package(package_content, Package::Source::Unknown),
    repo()
{
    buildTooltipsLinesMap();
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


void SiPackage::buildTooltipsLinesMap()
{
    numberToTooltipLine.insert(2, Package::TooltipLine::Name);
    numberToTooltipLine.insert(3, Package::TooltipLine::Version);
    numberToTooltipLine.insert(4, Package::TooltipLine::Description);
    numberToTooltipLine.insert(5, Package::TooltipLine::Architecture);
    numberToTooltipLine.insert(6, Package::TooltipLine::URL);
    numberToTooltipLine.insert(7, Package::TooltipLine::Licenses);
    numberToTooltipLine.insert(8, Package::TooltipLine::Groups);
    numberToTooltipLine.insert(9, Package::TooltipLine::Provides);
    numberToTooltipLine.insert(10, Package::TooltipLine::DependsOn);
    numberToTooltipLine.insert(11, Package::TooltipLine::OptionalDeps);
    numberToTooltipLine.insert(12, Package::TooltipLine::ConflictsWith);
    numberToTooltipLine.insert(13, Package::TooltipLine::Replaces);
    numberToTooltipLine.insert(14, Package::TooltipLine::DownloadSize);
    numberToTooltipLine.insert(15, Package::TooltipLine::InstalledSize);
    numberToTooltipLine.insert(16, Package::TooltipLine::Packager);
    numberToTooltipLine.insert(17, Package::TooltipLine::BuildDate);
    numberToTooltipLine.insert(18, Package::TooltipLine::ValidatedBy);
}
