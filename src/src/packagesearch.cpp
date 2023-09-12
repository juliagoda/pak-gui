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

#include "packagesearch.h"

#include "outputfilter.h"


PackageSearch::PackageSearch() :
    next_window(nullptr)
{
    // ...
}


QPointer<SearchWindow>& PackageSearch::setNext(QPointer<SearchWindow>& new_window)
{
    this->next_window = new_window;
    return this->next_window;
}


void PackageSearch::handle()
{
    if (this->next_window)
        this->next_window->handle();
}



PackageSearchInput::PackageSearchInput(const QSharedPointer<InstallCommandParser>& new_install_command_parser) :
    PackageSearch(),
    install_command_parser{new_install_command_parser},
    package_input_window{nullptr}
{
    // ...
}


void PackageSearchInput::handle()
{
    package_input_window.reset(new PackageInputWindow());
    connect(package_input_window.data(), &PackageInputWindow::packageNameInserted,
            [this](const QString& new_package_name)
    {
        install_command_parser->updatePackageName(new_package_name);
        PackageSearch::handle();
    });

    connect(package_input_window.data(), &PackageInputWindow::cancelled,
        [this]()
        {
            install_command_parser->stop();
            package_input_window->close();
            emit ended();
        });

    package_input_window->show();
}


void PackageSearchInput::closeWindow()
{
    if (!package_input_window.isNull())
        package_input_window->close();
}


SearchResultsList::SearchResultsList(const QSharedPointer<InstallCommandParser>& new_install_command_parser,
                                     const QSharedPointer<Process>& new_process,
                                     uint packages_to_update_count) :
    PackageSearch(),
    install_command_parser{new_install_command_parser},
    output_filter{new OutputFilter},
    process{new_process},
    search_all_command_parser{nullptr},
    choice_window{nullptr},
    packages_to_update{packages_to_update_count}
{
    connect(install_command_parser.get(), &InstallCommandParser::ended, [&]() { emit ended(); });
}


void SearchResultsList::handle()
{
    search_all_command_parser.reset(new SearchAllCommandParser(install_command_parser->getPackageName()));

    choice_window.reset(new ChoiceWindow(tr("Choose package")));
    connect(search_all_command_parser.get(), &SearchAllCommandParser::searchEnded, choice_window.get(),
            QOverload<const QStringList&>::of(&ChoiceWindow::fillComboBox));
    search_all_command_parser->retrieveInfo();
    connect(choice_window.get(), QOverload<const QString&>::of(&ChoiceWindow::choiceDefined), [this](const QString& chosen_package)
    {
        emit acceptedChoice();
        install_command_parser->updateTask(output_filter->getSourceFromSearchLine(chosen_package));
        install_command_parser->updatePackageName(output_filter->getPackageFromSearchLine(chosen_package));
        install_command_parser->start(process, packages_to_update);
    });

    choice_window->show();
}
