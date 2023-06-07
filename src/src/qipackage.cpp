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

#include "qipackage.h"

#include "defs.h"

#include <QTextStream>


QiPackage::QiPackage(const QString& package_content) :
    Package(package_content, Package::Source::Unknown)
{
    buildTooltipsLinesMap();
    updateData(package_content, Constants::packageQiNameLine(), Constants::packageQiVersionLine());
    setText(getName().trimmed() + "-" + getVersion().trimmed());
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Unchecked);
}


QiPackage::QiPackage(QiPackage& qi_package) :
    Package(qi_package)
{
    setName(qi_package.getName());
    setNo(qi_package.getNo());
    setVersion(qi_package.getVersion());
    setText(getName().trimmed() + "-" + getVersion().trimmed());
    setFlags(qi_package.flags());
    setCheckState(qi_package.checkState());
    setToolTip(qi_package.toolTip());
}


void QiPackage::buildTooltipsLinesMap()
{
    numberToTooltipLine.insert(1, Package::TooltipLine::Name);
    numberToTooltipLine.insert(2, Package::TooltipLine::Version);
    numberToTooltipLine.insert(3, Package::TooltipLine::Description);
    numberToTooltipLine.insert(4, Package::TooltipLine::Architecture);
    numberToTooltipLine.insert(5, Package::TooltipLine::URL);
    numberToTooltipLine.insert(6, Package::TooltipLine::Licenses);
    numberToTooltipLine.insert(7, Package::TooltipLine::Groups);
    numberToTooltipLine.insert(8, Package::TooltipLine::Provides);
    numberToTooltipLine.insert(9, Package::TooltipLine::DependsOn);
    numberToTooltipLine.insert(10, Package::TooltipLine::OptionalDeps);
    numberToTooltipLine.insert(11, Package::TooltipLine::RequiredBy);
    numberToTooltipLine.insert(12, Package::TooltipLine::OptionalFor);
    numberToTooltipLine.insert(13, Package::TooltipLine::ConflictsWith);
    numberToTooltipLine.insert(14, Package::TooltipLine::Replaces);
    numberToTooltipLine.insert(15, Package::TooltipLine::InstalledSize);
    numberToTooltipLine.insert(16, Package::TooltipLine::Packager);
    numberToTooltipLine.insert(17, Package::TooltipLine::BuildDate);
    numberToTooltipLine.insert(18, Package::TooltipLine::InstallDate);
    numberToTooltipLine.insert(19, Package::TooltipLine::InstallReason);
    numberToTooltipLine.insert(20, Package::TooltipLine::InstallScript);
    numberToTooltipLine.insert(21, Package::TooltipLine::ValidatedBy);
}
