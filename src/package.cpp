#include "package.h"

#include <QTextStream>
#include <QDebug>

#include "defs.h"


Package::Package(QString& package_content) :
    name(),
    version(),
    description(),
    dependencies()
{
    updateData(package_content);
}


void Package::updateData(QString& packageContent)
{
    QStringList lines = packageContent.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

    int name_separator_index = lines.at(PACKAGE_NAME_LINE).indexOf(": ") + 1;
    setName(lines.at(PACKAGE_NAME_LINE).mid(name_separator_index));

    int version_separator_index = lines.at(PACKAGE_VERSION_LINE).indexOf(": ") + 1;
    setVersion(lines.at(PACKAGE_VERSION_LINE).mid(version_separator_index));

    int description_separator_index = lines.at(PACKAGE_DESCRIPTION_LINE).indexOf(": ") + 1;
    setDescription(lines.at(PACKAGE_DESCRIPTION_LINE).mid(description_separator_index));

    int dependencies_separator_index = lines.at(PACKAGE_DEPENDENCIES_LINE).indexOf(": ") + 1;
    setDependencies(lines.at(PACKAGE_DEPENDENCIES_LINE).mid(dependencies_separator_index));
}


const QString& Package::getName() const
{
    return name;
}


const QString& Package::getVersion() const
{
    return version;
}


const QString& Package::getDescription() const
{
    return description;
}


const QString& Package::getDependencies() const
{
    return dependencies;
}


void Package::setName(const QString& new_name)
{
    qDebug() << "Set package name: " << new_name;
    name = new_name;
}


void Package::setVersion(const QString& new_version)
{
    qDebug() << "Set package version: " << new_version;
    version = new_version;
}


void Package::setDescription(const QString& new_description)
{
    qDebug() << "Set package description: " << new_description;
    description = new_description;
}


void Package::setDependencies(const QString& new_dependencies)
{
    qDebug() << "Set package dependencies: " << new_dependencies;
    dependencies = new_dependencies;
}
