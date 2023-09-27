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
    setType(Package::Type::Qi);
    Constants constants;
    updateData(package_content, constants.packageQiNameLine(), constants.packageQiVersionLine());
    setText(getName().trimmed() + "-" + getVersion().trimmed());
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Unchecked);
}


QiPackage::QiPackage(const QiPackage& qi_package) :
    Package(qi_package)
{
    setName(qi_package.getName());
    setNo(qi_package.getNo());
    setType(qi_package.getType());
    setSource(qi_package.getSource());
    setVersion(qi_package.getVersion());
    setText(getName().trimmed() + "-" + getVersion().trimmed());
    setFlags(qi_package.flags());
    setCheckState(qi_package.checkState());
    setToolTip(qi_package.toolTip());
}


QiPackage& QiPackage::operator=(const QiPackage& qi_package)
{
    setName(qi_package.getName());
    setNo(qi_package.getNo());
    setType(qi_package.getType());
    setSource(qi_package.getSource());
    setVersion(qi_package.getVersion());
    setText(getName().trimmed() + "-" + getVersion().trimmed());
    setFlags(qi_package.flags());
    setCheckState(qi_package.checkState());
    setToolTip(qi_package.toolTip());
    return *this;
}


QiPackage::QiPackage(QiPackage&& qi_package) :
    Package(qi_package)
{
    setName(qi_package.getName());
    setNo(qi_package.getNo());
    setType(qi_package.getType());
    setSource(qi_package.getSource());
    setVersion(qi_package.getVersion());
    setText(getName().trimmed() + "-" + getVersion().trimmed());
    setFlags(qi_package.flags());
    setCheckState(qi_package.checkState());
    setToolTip(qi_package.toolTip());
}


QiPackage& QiPackage::operator=(QiPackage&& qi_package)
{
    setName(qi_package.getName());
    setNo(qi_package.getNo());
    setType(qi_package.getType());
    setSource(qi_package.getSource());
    setVersion(qi_package.getVersion());
    setText(getName().trimmed() + "-" + getVersion().trimmed());
    setFlags(qi_package.flags());
    setCheckState(qi_package.checkState());
    setToolTip(qi_package.toolTip());
    return *this;
}


QListWidgetItem* QiPackage::clone() const
{
    return new QiPackage(*this);
}
