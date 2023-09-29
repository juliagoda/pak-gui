// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of tests for  package manager (based on "pak" application).
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

#include "checkpackagetest.h"


TestCheckPackage::TestCheckPackage(QObject* parent) :
    QObject{parent},
    check_package{"binutils 2.40-1.1 => 2.40-2.1",
                  Package::Source::Repo}
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestCheckPackage::isItemCheckable()
{
    QCOMPARE(check_package.flags(), Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
}


void TestCheckPackage::isItemNotCheckedByDefault()
{
    QCOMPARE(check_package.checkState(), Qt::Unchecked);
}


void TestCheckPackage::isItemNameEqualToBinutils()
{
    QCOMPARE(check_package.getName(), QString("binutils"));
}


void TestCheckPackage::isItemVersionCorrectlyVisible()
{
    QCOMPARE(check_package.getVersion(), QString("2.40-1.1 => 2.40-2.1"));
}


void TestCheckPackage::isSourceEqualToRepo()
{
    QCOMPARE(check_package.getSource(), Package::Source::Repo);
}
