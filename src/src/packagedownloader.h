// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of  package manager based on "pak" application.
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

#pragma once

#include "downloadcommandparser.h"

#include "packageinputwindow.h"
#include "choicewindow.h"

#include <QString>
#include <QPointer>
#include <QSharedPointer>
#include <QMessageBox>


class PackageInputWindow;

class DownloaderWindow : public QObject
{
    Q_OBJECT

 public:
    virtual QPointer<DownloaderWindow>& setNext(QPointer<DownloaderWindow>& new_window) = 0;
    virtual ~DownloaderWindow() = default;
    virtual void handle() = 0;

 signals:
    void ended();
};


class PackageDownloader : public DownloaderWindow
{
    Q_OBJECT

 private:
    QPointer<DownloaderWindow> next_window;

 public:
    PackageDownloader();

    QPointer<DownloaderWindow>& setNext(QPointer<DownloaderWindow>& new_window) override;
    void handle() override;
};


class PackageInput : public PackageDownloader
{
    Q_OBJECT

 public:
    PackageInput(const QSharedPointer<DownloadCommandParser>& new_download_command_parser);

    void handle() override;

 public slots:
    void closeWindow();

 private:
    QScopedPointer<PackageInputWindow> package_input_window;
    QSharedPointer<DownloadCommandParser> download_command_parser;
};


class PathsChoiceInput : public PackageDownloader
{
    Q_OBJECT

 public:
    PathsChoiceInput(const QSharedPointer<DownloadCommandParser>& new_download_command_parser);

    void handle() override;

 signals:
    void acceptedChoice();

 private:
    QSharedPointer<DownloadCommandParser> download_command_parser;
    QScopedPointer<ChoiceWindow> choice_window;
};
