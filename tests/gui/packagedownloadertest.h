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

#pragma once

#include "packagedownloader.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockPackageDownloader : public PackageDownloader
{
    Q_OBJECT

public:
    explicit MockPackageDownloader();
    friend class TestPackageDownloader;
};


class MockPackageInput : public PackageInput
{
    Q_OBJECT

public:
    explicit MockPackageInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser);
    friend class TestPackageDownloader;
};


class MockPathsChoiceInput : public PathsChoiceInput
{
    Q_OBJECT

public:
    explicit MockPathsChoiceInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser);
    friend class TestPackageDownloader;
};


class MockReposChoiceInput : public ReposChoiceInput
{
    Q_OBJECT

public:
    explicit MockReposChoiceInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser);
    friend class TestPackageDownloader;
};


class TestPackageDownloader : public QObject
{
    Q_OBJECT

public:
    TestPackageDownloader(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockPackageDownloader package_downloader;
    MockPackageInput package_input;
    MockPathsChoiceInput paths_choice_input;
    MockReposChoiceInput repos_choice_input;
    QSharedPointer<DownloadCommandParser> download_command_parser = QSharedPointer<DownloadCommandParser>(nullptr);
};
