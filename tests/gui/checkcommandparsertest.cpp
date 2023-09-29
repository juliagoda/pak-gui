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

#include "checkcommandparsertest.h"

#include <QHash>


QString MockCheckCommandParser::generatePakCheckResults()
{
    return QString{":: Latest Arch Linux news: 2\n"
                   "...\n"
                   ":: System\n"
                   "Checking...\n"
                   "\n"
                   "Packages to update:\n"
                   "acl                             2.3.1-2.1 => 2.3.1-3.1\n"
                   "akonadi                         22.12.1-2.1 => 22.12.2-1.1\n"
                   ":: AUR\n"
                   "auracle-git (AUR) is not installed\n"
                   "\n"
                   ":: POLAUR\n"
                   "Checking...\n"
                   "\n"
                   "Packages to update:\n"
                   "repo-refreshed/konsole          22.12.1-1.1 => 22.12.2-1.4\n"
                   "\n"
                   ":: Unmerged pacnew/pacsave files\n"
                   "\n"
                   "...\n"};
}


TestCheckCommandParser::TestCheckCommandParser(QObject* parent) :
    QObject{parent},
    check_command_parser()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestCheckCommandParser::retrievedPackagesMapCountIsEqualToThree()
{
    auto results_map = check_command_parser.retrieveInfoMap();
    QCOMPARE(results_map.count(), 3);
}


void TestCheckCommandParser::retrievedPackagesMapContainsAclPackagesFromRepo()
{
   auto results_map = check_command_parser.retrieveInfoMap();
   QCOMPARE(results_map.value("acl 2.3.1-2.1 => 2.3.1-3.1"), Package::Source::Repo);
}


void TestCheckCommandParser::retrievedPackagesMapContainsKonsolePackageFromPolaur()
{
   auto results_map = check_command_parser.retrieveInfoMap();
   QCOMPARE(results_map.value("repo-refreshed/konsole 22.12.1-1.1 => 22.12.2-1.4"), Package::Source::POLAUR);
}
