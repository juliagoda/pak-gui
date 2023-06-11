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

#include "pathconverter.h"
#include "src/outputfilter.h"

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QMutex>


class Logger : public QObject
{
    Q_OBJECT

public:
    enum class WriteOperations
    {
        Update = 0,
        Install,
        Remove,
        Clean,
        Download,
        UpdateAll,
        CheckUpdates,
        CheckAvailable,
        CheckInstalled,
        ShowStatistics,
        MirrorsUpdate,
        UpdateInstalled,
        PrintVCSPackages,
        SearchAll
    };
    Q_ENUM(WriteOperations)

    static Logger* logger();
    ~Logger() override;
    Logger(Logger& instance) = delete;

    void operator=(const Logger& instance) = delete;
    void writeToFile(QString& text, WriteOperations section);
    void writeSectionToFile(WriteOperations section);
    void writeLineToFile(QString& line);
    void logInfo(const QString& text);
    void logWarning(const QString& text);
    void logFatal(const QString& text);
    void logDebug(const QString& text);

public Q_SLOTS:
    void clearLogsFile();
    void reopenFile();

protected:
    explicit Logger();
    void clearStreamText();
    const QString& streamTextResult() const;
    void logIntoFile(const QString& section, const QString& text);

private:
    void appendSection(WriteOperations section);
    void appendSeparator();
    void appendNewLine();
    bool isWritePossible();
    void closeOnQuit();
    void resizeFileSizeNotWithinRange();
    bool validate();
    void writeToStream();

    QFile logs_file = QFile(PathConverter::fullConfigPath());
    QScopedPointer<OutputFilter> output_filter = QScopedPointer<OutputFilter>(new OutputFilter);
    QString stream_text;
    QTextStream output_stream;
    static Logger* instance;
    static QMutex write_mutex;
};

