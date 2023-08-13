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

#include "packagedownloader.h"


PackageDownloader::PackageDownloader() :
    next_window(nullptr)
{
   // ...
}


QPointer<DownloaderWindow> &PackageDownloader::setNext(QPointer<DownloaderWindow>& new_window)
{
    this->next_window = new_window;
    return this->next_window;
}


void PackageDownloader::handle()
{
    if (this->next_window)
        this->next_window->handle();
}


PackageInput::PackageInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser) :
    PackageDownloader(),
    package_input_window(nullptr),
    download_command_parser(new_download_command_parser)
{
   // ...
}


void PackageInput::handle()
{
    package_input_window.reset(new PackageInputWindow());
    connect(package_input_window.data(), &PackageInputWindow::packageNameInserted,
            [this](const QString& new_package_name)
    {
        download_command_parser->updatePackageName(new_package_name);
        PackageDownloader::handle();
    });

    connect(package_input_window.data(), &PackageInputWindow::cancelled,
        [this]()
        {
            download_command_parser->stop();
            package_input_window->close();
            emit ended();
        });

    package_input_window->show();
}


void PackageInput::closeWindow()
{
    if (!package_input_window.isNull())
        package_input_window->close();
}


PathsChoiceInput::PathsChoiceInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser) :
    PackageDownloader(),
    download_command_parser(new_download_command_parser),
    choice_window(nullptr)
{
   // ...
}


void PathsChoiceInput::handle()
{
    choice_window.reset(new ChoiceWindow(i18n("Choose path for package save")));
    connect(download_command_parser.get(), &DownloadCommandParser::continuePathsRetrieve, choice_window.get(),
            QOverload<QString&>::of(&ChoiceWindow::fillComboBox));
    download_command_parser->start();
    connect(choice_window.data(), QOverload<int>::of(&ChoiceWindow::choiceDefined), [this](int new_index)
    {
        download_command_parser->inputAnswer(QString::number(new_index));
        download_command_parser->updateDirectoryChoice(new_index);
        PackageDownloader::handle();
    });

    connect(choice_window.data(), &ChoiceWindow::cancelled,
        [this]()
        {
            download_command_parser->stop();
            choice_window->close();
        });

    choice_window->show();
}


ReposChoiceInput::ReposChoiceInput(QSharedPointer<DownloadCommandParser> &new_download_command_parser) :
    PackageDownloader(),
    download_command_parser(new_download_command_parser),
    choice_window(nullptr)
{
    connect(download_command_parser.get(), &DownloadCommandParser::ended, [this]{ emit ended() ; });
}


void ReposChoiceInput::handle()
{
    choice_window.reset(new ChoiceWindow(i18n("Choose repo for package download")));
    connect(download_command_parser.get(), &DownloadCommandParser::continueReposRetrieve, choice_window.get(),
            QOverload<QString&>::of(&ChoiceWindow::fillComboBox));
    connect(choice_window.data(), QOverload<int>::of(&ChoiceWindow::choiceDefined), [this](int new_index)
    {
        emit acceptedChoice();
        download_command_parser->inputAnswer(QString::number(new_index));
    });

    connect(choice_window.data(), &ChoiceWindow::cancelled,
        [this]()
        {
            download_command_parser->stop();
            choice_window->close();
        });

    choice_window->show();
}
