// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of CachyOS package manager based on "pak" application.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "package.h"

#include "settings.h"
#include "algorithms.h"
#include "defs.h"
#include "logger.h"


Package::Package(const QString& package_content, Source new_source) :
    QListWidgetItem(),
    source{new_source}
{
    Q_UNUSED(package_content)
}


Package::Package(const Package& package) :
    QListWidgetItem()
{
    name = package.name;
    version = package.version;
    source = package.source;
    no = package.no;
    package_type = package.package_type;
    setToolTip(package.toolTip());
}


Package& Package::operator=(const Package& package)
{
    name = package.name;
    version = package.version;
    source = package.source;
    no = package.no;
    package_type = package.package_type;
    setToolTip(package.toolTip());
    return *this;
}


Package::Package(Package&& package)
{
    name = package.name;
    version = package.version;
    source = package.source;
    no = package.no;
    package_type = package.package_type;
    setToolTip(package.toolTip());
}


Package& Package::operator=(Package&& package)
{
    name = package.name;
    version = package.version;
    source = package.source;
    no = package.no;
    package_type = package.package_type;
    setToolTip(package.toolTip());
    return *this;
}


int Package::getNo() const
{
    return no;
}


const QString &Package::getName() const
{
    return name;
}


const QString &Package::getVersion() const
{
    return version;
}


auto Package::getSource() const -> Source
{
    return source;
}


void Package::setNo(const int new_no)
{
    no = new_no;
}


auto Package::getType() const -> Type
{
    return package_type;
}


QListWidgetItem *Package::clone() const
{
    return new Package(*this);
}


bool Package::operator<(const QListWidgetItem& other) const
{
    auto& package = dynamic_cast<const Package&>(other);
    if (no != -1 && package.no != 1)
        return no < package.no;

    return name < package.name;
}


void Package::updateData(const QString& package_content, int name_line, int version_line)
{
    const QStringList& lines = package_content.split(QRegExp("[\r\n]"), Qt::SkipEmptyParts);

    if (lines.count() == 0)
        return;

    setToolTipOnPackage(package_content);
    setNameParameter(name_line, lines);
    setVersionParameter(version_line, lines);
}


void Package::setNameParameter(int parameter_line,
                               const QStringList& lines)
{
    if (!validate(lines, parameter_line + 1, QString("updateData()")))
        return;

    int parameter_separator_index = lines.at(parameter_line).indexOf(": ") + 1;
    setName(lines.at(parameter_line).mid(parameter_separator_index));
}


void Package::setVersionParameter(int parameter_line,
                                  const QStringList& lines)
{
    if (!validate(lines, parameter_line + 1, QString("updateData()")))
        return;

    int parameter_separator_index = lines.at(parameter_line).indexOf(": ") + 1;
    setVersion(lines.at(parameter_line).mid(parameter_separator_index));
}


void Package::setToolTipOnPackage(const QString& text)
{
    auto selected_info_list = Settings::records()->packagesInfoSelected();

    QScopedPointer<Algorithms> algorithms(new Algorithms);
    QString splitting_text{" : "};
    Constants constants;
    const auto& results = algorithms->createSplittedList<Package::TooltipLine>(text, splitting_text,
        selected_info_list, constants.typePackageToTooltipLines(getType()));

    setToolTip(results.join(QString("\n")));
}


bool Package::validate(const QStringList& lines, int expected_size, const QString& funtion_name)
{
    if (lines.size() < expected_size)
    {
        Logger::logger()->logFatal(QString("There are not enough lines in list. Abort %1").arg(funtion_name));
        return false;
    }

    return true;
}


void Package::setName(const QString &new_name)
{
    name = new_name;
}


void Package::setVersion(const QString &new_version)
{
    version = new_version;
}


void Package::setSource(Source new_source)
{
    source = new_source;
}


void Package::setType(Type new_package_type)
{
    package_type = new_package_type;
}
