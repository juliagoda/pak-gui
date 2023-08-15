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

#include "sipackage.h"

#include "defs.h"


SiPackage::SiPackage(const QString& package_content) :
    Package(package_content, Package::Source::Unknown),
    repo()
{
    setType(Package::Type::Si);
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
    setType(si_package.getType());
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
    QStringList lines = package_content.split(QRegExp("[\r\n]"), Qt::SkipEmptyParts);

    if (lines.count() == 0)
        return;

    setRepoParameter(lines);
    setNameParameter(lines);
    setVersionParameter(lines);
}


void SiPackage::setRepoParameter(const QStringList& lines)
{
    if (!validate(lines, Constants::packageSiRepoName() + 1, QString("updateData()")))
        return;

    int repo_separator_index = lines.at(Constants::packageSiRepoName()).indexOf(": ") + 1;
    setRepo(lines.at(Constants::packageSiRepoName()).mid(repo_separator_index));
}


void SiPackage::setNameParameter(const QStringList& lines)
{
    if (!validate(lines, Constants::packageSiNameLine() + 1, QString("updateData()")))
        return;

    int name_separator_index = lines.at(Constants::packageSiNameLine()).indexOf(": ") + 1;
    setName(lines.at(Constants::packageSiNameLine()).mid(name_separator_index));
}


void SiPackage::setVersionParameter(const QStringList& lines)
{
    if (!validate(lines, Constants::packageSiVersionLine() + 1, QString("updateData()")))
        return;

    int version_separator_index = lines.at(Constants::packageSiVersionLine()).indexOf(": ") + 1;
    setVersion(lines.at(Constants::packageSiVersionLine()).mid(version_separator_index));
}
