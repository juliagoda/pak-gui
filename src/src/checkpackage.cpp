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

#include "checkpackage.h"

#include <QRegularExpression>


CheckPackage::CheckPackage(const QString& new_package_content, Package::Source new_source) :
    Package{new_package_content, new_source}
{
    if (new_package_content.isEmpty())
        return;

    setType(Package::Type::Check);
    updateData(new_package_content, 0, 0);
    setText(getName() + "-" + getVersion());
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Unchecked);
}


CheckPackage::CheckPackage(const CheckPackage& check_package) :
    Package{check_package}
{
   setName(check_package.getName());
   setNo(check_package.getNo());
   setType(check_package.getType());
   setSource(check_package.getSource());
   setVersion(check_package.getVersion());
   setText(getName().trimmed() + "-" + getVersion().trimmed());
   setFlags(check_package.flags());
   setCheckState(check_package.checkState());
}


CheckPackage& CheckPackage::operator=(const CheckPackage& check_package)
{
   setName(check_package.getName());
   setNo(check_package.getNo());
   setType(check_package.getType());
   setSource(check_package.getSource());
   setVersion(check_package.getVersion());
   setText(getName().trimmed() + "-" + getVersion().trimmed());
   setFlags(check_package.flags());
   setCheckState(check_package.checkState());
   return *this;
}


CheckPackage::CheckPackage(CheckPackage&& check_package) :
    Package{check_package}
{
   setName(check_package.getName());
   setNo(check_package.getNo());
   setType(check_package.getType());
   setSource(check_package.getSource());
   setVersion(check_package.getVersion());
   setText(getName().trimmed() + "-" + getVersion().trimmed());
   setFlags(check_package.flags());
   setCheckState(check_package.checkState());
}


CheckPackage& CheckPackage::operator=(CheckPackage&& check_package)
{
   setName(check_package.getName());
   setNo(check_package.getNo());
   setType(check_package.getType());
   setSource(check_package.getSource());
   setVersion(check_package.getVersion());
   setText(getName().trimmed() + "-" + getVersion().trimmed());
   setFlags(check_package.flags());
   setCheckState(check_package.checkState());
   return *this;
}


QListWidgetItem* CheckPackage::clone() const
{
   return new CheckPackage(*this);
}


void CheckPackage::updateData(const QString& package_content, int name_line, int version_line)
{
    Q_UNUSED(name_line)
    Q_UNUSED(version_line)

    static QRegularExpression whitespace_expression(" ");
    static QRegularExpression numbers_expression("[0-9]");
    int first_whitespace_index = package_content.indexOf(whitespace_expression);
    int first_number_index = package_content.indexOf(numbers_expression);

    QString name_part = package_content.left(first_whitespace_index);
    setName(name_part);

    QString version_part = package_content.mid(first_number_index);
    setVersion(version_part);
}
