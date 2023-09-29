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

#include "packagesearchtest.h"


MockPackageSearch::MockPackageSearch() :
    PackageSearch()
{
  // ...
}


MockPackageSearchInput::MockPackageSearchInput(QSharedPointer<InstallCommandParser>& new_install_command_parser) :
    PackageSearchInput(new_install_command_parser)
{
  // ...
}


MockSearchResultsList::MockSearchResultsList(QSharedPointer<InstallCommandParser>& new_install_command_parser,
                                             QSharedPointer<Process>& new_process,
                                             uint packages_to_update_count) :
    SearchResultsList(new_install_command_parser, new_process, packages_to_update_count)
{
  // ...
}


TestPackageSearch::TestPackageSearch(QObject* parent) :
    QObject(parent),
    package_search(),
    package_search_input(install_command_parser),
    search_results_list(install_command_parser,
                        process,
                        packages_to_update_count)
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestPackageSearch::cleanup()
{
  // ...
}
