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

#include "pathconvertertest.h"

#include "pathconverter.h"


TestPathConverter::TestPathConverter(QObject* parent) :
    QObject{parent}
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestPathConverter::isRelativePathConvertedToAbsolutePath()
{
    const QRegExp regex{"/home/\\w+/path/example"};
    const QString path{"~/path/example"};

    QVERIFY(regex.exactMatch(PathConverter::toAbsolutePath(path)));
}


void TestPathConverter::isAbsolutePathTheSameAfterConversion()
{
    const QString path{"/home/someone/path/example"};

    QCOMPARE(PathConverter::toAbsolutePath(path), QString("/home/someone/path/example"));
}


void TestPathConverter::hasFullConfigPathCorrectForm()
{
   QCOMPARE(PathConverter::fullConfigPath(), QString("~/.config/pak-gui/logs.txt"));
}
