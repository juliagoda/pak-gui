// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of tests for CachyOS package manager (based on "pak" application).
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

#include "sicommandparsertest.h"

#include "packagescolumnfixtures.h"


QString MockSiCommandParser::generateResult()
{
    QString a52dec = package_content_a52dec_si;
    return a52dec.append("\n").append(package_content_alsa_utils_si);
}


TestSiCommandParser::TestSiCommandParser(QObject* parent) :
    QObject(parent),
    si_command_parser()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestSiCommandParser::initTestCase_data()
{
    QTest::addColumn<QStringList>("command_parser_results");
    QTest::newRow("si") << si_command_parser.retrieveInfo();
}


void TestSiCommandParser::isListContainingTwoPackages()
{
    QFETCH_GLOBAL(QStringList, command_parser_results);
    QCOMPARE(command_parser_results.count(), 2);
}


void TestSiCommandParser::isListContainingPackagesWithCorrectContent()
{
    QFETCH_GLOBAL(QStringList, command_parser_results);
    QCOMPARE(QStringLiteral("%1\n").arg(command_parser_results.constFirst().data()), package_content_a52dec_si);
    QCOMPARE(command_parser_results.constLast().data(), package_content_alsa_utils_si);
}
