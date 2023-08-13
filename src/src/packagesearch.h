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

#pragma once

#include "installcommandparser.h"
#include "searchallcommandparser.h"
#include "packageinputwindow.h"
#include "choicewindow.h"

#include "process.h"
#include "qscopedpointer.h"
#include "src/outputfilter.h"

#include <QString>
#include <QPointer>
#include <QSharedPointer>
#include <QMessageBox>
#include <QProcess>


class SearchWindow : public QObject
{
    Q_OBJECT

public:
    virtual QPointer<SearchWindow>& setNext(QPointer<SearchWindow>& new_window) = 0;
    virtual ~SearchWindow() override = default;
    virtual void handle() = 0;

 signals:
    void ended();
};


class PackageSearch : public SearchWindow
{
    Q_OBJECT

private:
    QPointer<SearchWindow> next_window;

public:
    PackageSearch();

    QPointer<SearchWindow>& setNext(QPointer<SearchWindow>& new_window) override;
    void handle() override;
};


class PackageSearchInput : public PackageSearch
{
    Q_OBJECT

public:
    PackageSearchInput(QSharedPointer<InstallCommandParser>& new_install_command_parser);

    void handle() override;

public Q_SLOTS:
    void closeWindow();

private:
    QSharedPointer<InstallCommandParser> install_command_parser;
    QScopedPointer<PackageInputWindow> package_input_window;
};


class SearchResultsList : public PackageSearch
{
    Q_OBJECT

public:
    SearchResultsList(QSharedPointer<InstallCommandParser>& new_install_command_parser,
                      QSharedPointer<Process>& new_process,
                      uint packages_to_update_count);

    void handle() override;

signals:
    void acceptedChoice();

private:
    QSharedPointer<InstallCommandParser> install_command_parser;
    QScopedPointer<OutputFilter> output_filter;
    QSharedPointer<Process> process;
    QScopedPointer<SearchAllCommandParser> search_all_command_parser;
    QScopedPointer<ChoiceWindow> choice_window;
    uint packages_to_update;
};
