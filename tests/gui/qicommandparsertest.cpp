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

#include "qicommandparsertest.h"

#include "packagescolumnfixtures.h"


QString MockQiCommandParser::generateResult()
{
    QString gimp = package_content_gimp;
    return gimp.append("\n").append(package_content_a52dec);
}


TestQiCommandParser::TestQiCommandParser(QObject* parent) :
    QObject(parent),
    qi_command_parser()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestQiCommandParser::initTestCase_data()
{
   QTest::addColumn<QStringList>("command_parser_results");
   QTest::newRow("qi") << qi_command_parser.retrieveInfo();
}


void TestQiCommandParser::isListContainingTwoPackages()
{
   QFETCH_GLOBAL(QStringList, command_parser_results);
   QCOMPARE(command_parser_results.count(), 2);
}


void TestQiCommandParser::isListContainingPackagesWithCorrectContent()
{
    QFETCH_GLOBAL(QStringList, command_parser_results);
    QCOMPARE(QStringLiteral("%1\n").arg(command_parser_results.constFirst().data()), package_content_gimp);
    QCOMPARE(command_parser_results.constLast().data(), package_content_a52dec);
}
