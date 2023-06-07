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

#include "statisticscommandparsertest.h"


QString MockStatisticsCommandParser::generateResult()
{
    return QString(":: Statistics by month: 2023-02\n"
                   "\n"
                   "Install actions: 34\n"
                   "\n"
                   "Downgrade actions: 20\n"
                   "\n"
                   "Remove actions: 23\n"
                   "\n"
                   "Update actions: 12\n");
}



TestStatisticsCommandParser::TestStatisticsCommandParser(QObject* parent) :
    QObject(parent),
    statistics_command_parser()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestStatisticsCommandParser::statisticsActionsAreCorrectlyAddedToList()
{
    auto list = statistics_command_parser.retrieveInfo();

    QCOMPARE(list.join("\n"), QString("Install actions: 34\nDowngrade actions: 20\nRemove actions: 23\nUpdate actions: 12"));
}


void TestStatisticsCommandParser::statisticActionsListIsCorrectlyConvertedToMap()
{
    auto list = statistics_command_parser.retrieveInfo();
    auto map = statistics_command_parser.convertToMap(list);

    QCOMPARE(map.value("Install actions"), 34);
    QCOMPARE(map.value("Downgrade actions"), 20);
    QCOMPARE(map.value("Remove actions"), 23);
    QCOMPARE(map.value("Update actions"), 12);
}
