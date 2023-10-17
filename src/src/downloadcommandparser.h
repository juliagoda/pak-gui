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

#include "commandparser.h"
#include "src/outputfilter.h"

#include <QProcess>
#include <QScopedPointer>
#include <QString>
#include <QMap>

class DownloadCommandParser : public CommandParser
{
    Q_OBJECT

public:
    DownloadCommandParser(const QString& new_package_name, QWidget* new_parent);
    ~DownloadCommandParser() override = default;

    void updatePackageName(const QString& new_package_name);
    virtual void start();
    virtual void stop();
    QStringList retrieveInfo() override;
    virtual void inputAnswer(const QString& new_answer);
    void updateDirectoryChoice(int directory_no);

protected:
    virtual void showWarningWhenNameEmpty();
    virtual void connectSignals();
    void processReadLine(QString& line, int& directories_line_count);
    bool isPackageAlreadyDownloaded();

Q_SIGNALS:
    void continuePathsRetrieve(const QString& output);
    void ended();

protected Q_SLOTS:
    virtual bool validateFinishedOutput(int exit_code, QProcess::ExitStatus exit_status);
    virtual void showDirectory(int exit_code, QProcess::ExitStatus exit_status);

private:
    bool validate();
    void fillDirectoriesMap(const QString& result);
    void addLineToDirectoriesMap(const QString& result);
    void processForDirectories(const QString& filtered_line, int& directories_line_count);

    using DirectoryNo = int;
    using DirectoryPath = QString;

    QScopedPointer<QProcess> pak_download{nullptr};
    QScopedPointer<OutputFilter> output_filter{new OutputFilter};
    QString package_name{};
    QString command{"pak -G"};
    QString result_output{};
    QStringList error_lines{};
    QWidget* parent{nullptr};
    QMap<DirectoryNo, DirectoryPath> directories_map{};
    int directory_no_choice{-1};
    bool isTerminated{false};
};

