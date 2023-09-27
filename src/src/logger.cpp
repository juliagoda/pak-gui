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

#include "logger.h"

#include "outputfilter.h"
#include "sizeconverter.h"
#include "settings.h"

#include <QDebug>
#include <QMetaEnum>


Logger* Logger::instance{nullptr};
QMutex Logger::write_mutex;


Logger::Logger()
{
    reopenFile();
}


void Logger::clearStreamText()
{
    stream_text.clear();
    stream_text = "";
}


const QString& Logger::streamTextResult() const
{
    return stream_text;
}


Logger::~Logger()
{
    closeFile();
}


Logger* Logger::logger()
{
    if (instance == nullptr)
        instance = new Logger();

    return instance;
}


void Logger::writeToFile(const QString& text, WriteOperations section)
{
    appendSection(section);
    appendNewLine();
    stream_text += output_filter->filteredOutput(text);
    appendNewLine();
    appendSeparator();
    appendNewLine();
    appendNewLine();

#ifdef RUN_TESTS
    return;
#endif

    if (!validate())
    {
        clearStreamText();
        return;
    }

    writeToStream();
}


void Logger::writeSectionToFile(WriteOperations section)
{
    appendSection(section);
    appendNewLine();

#ifdef RUN_TESTS
    return;
#endif

    if (!validate())
    {
        clearStreamText();
        return;
    }

    writeToStream();
}


void Logger::writeLineToFile(const QString& line)
{
    stream_text += output_filter->filteredOutput(line);
    appendNewLine();

#ifdef RUN_TESTS
    return;
#endif

    if (!validate())
    {
        clearStreamText();
        return;
    }

    writeToStream();
}


void Logger::logInfo(const QString &text)
{
    if (Settings::records()->hideInfoLogs())
        return;

    qInfo() << "[INFO] " << text;

    if (!Settings::records()->saveLogsIntoFile())
    {
        clearStreamText();
        return;
    }

    logIntoFile(QString("INFO"), text);
}


void Logger::logWarning(const QString &text)
{
    qWarning() << "[WARNING] " << text;

    if (!Settings::records()->saveLogsIntoFile())
    {
        clearStreamText();
        return;
    }

    logIntoFile(QString("WARNING"), text);
}


void Logger::logFatal(const QString &text)
{
    qCritical() << "[FATAL] " << text;

    if (!Settings::records()->saveLogsIntoFile())
    {
        clearStreamText();
        return;
    }

    logIntoFile(QString("FATAL"), text);
}


void Logger::logDebug(const QString &text)
{
    if (!Settings::records()->showDebug())
        return;

    qDebug() << "[DEBUG] " << text;

    if (!Settings::records()->saveLogsIntoFile())
    {
        clearStreamText();
        return;
    }

    logIntoFile(QString("DEBUG"), text);
}


void Logger::closeFile()
{
    if (logs_file.isOpen())
        logs_file.close();

    if (logs_file.isOpen())
        logWarning(QStringLiteral("Logs file \"%1\" couldn't be properly closed!").arg(logs_file.fileName()));
}


void Logger::clearLogsFile()
{
#ifdef RUN_TESTS
    return;
#endif

    qInfo() << "[INFO] " << QStringLiteral("Clear logs file - %1").arg(QDateTime::currentDateTime().toString());

    if (!logs_file.resize(0))
        qWarning() << "[WARNING] " << QStringLiteral("Logs file couldn't be removed: %1").arg(logs_file.errorString());
}


void Logger::appendSection(WriteOperations section)
{
    QString section_text{QVariant::fromValue(section).toString()};
    QString local_time{QDateTime::currentDateTime().toLocalTime().toString()};
    QString line{QString("\n\n\n---------------[").append(section_text.toUpper()).append(QString("]---------------"))};
    stream_text += local_time;
    stream_text += line;
}


void Logger::appendSeparator()
{
    stream_text += QString("////////////////////////////////////////////////////////////");
}


void Logger::appendNewLine()
{
    stream_text += QString("\n\n");
}


void Logger::logIntoFile(const QString& section, const QString& text)
{
    QString local_time{QDateTime::currentDateTime().toLocalTime().toString()};
    stream_text += " [" + section + "]  " + output_filter->filteredOutput(text) + "  (" + local_time + ")\n";

#ifdef RUN_TESTS
    return;
#endif

    if (!Settings::records()->saveLogsIntoFile())
    {
        clearStreamText();
        return;
    }

    if (!logs_file.exists())
        reopenFile();

    write_mutex.lock();
    resizeFileSizeNotWithinRange();
    output_stream << streamTextResult();
    clearStreamText();
    output_stream.resetStatus();
    output_stream.reset();
    write_mutex.unlock();
}


bool Logger::isWritePossible()
{
    if (logs_file.exists() && logs_file.isOpen() && logs_file.isWritable())
        return true;

    logWarning(QStringLiteral("Cannot write to file \"%1\" - file is not opened or you don't have permissions to write into or even doesn't exist").arg(logs_file.fileName()));
    return false;
}


void Logger::closeOnQuit()
{
#ifdef RUN_TESTS
    closeFile();
    return;
#endif

    delete instance;
}


void Logger::reopenFile()
{
#ifdef RUN_TESTS
    return;
#endif

    if (logs_file.isOpen())
        logs_file.close();

    output_stream.resetStatus();
    output_stream.reset();

    if (QString::compare(PathConverter::toAbsolutePath(logs_file.fileName()), PathConverter::fullConfigPath()) != 0)
        logs_file.setFileName(PathConverter::fullConfigPath());

    logs_file.open(QIODevice::ReadWrite | QIODevice::Append);
    output_stream.setDevice(&logs_file);

    if (logs_file.isOpen())
        logInfo(QStringLiteral("Logs file \"%1\" successfully opened\n").arg(logs_file.fileName()));
}


void Logger::resizeFileSizeNotWithinRange()
{
    int size_limit{Settings::records()->historyFileSizeLimitMb()};
    if (size_limit == 0)
        return;

    if (!logs_file.isOpen())
        reopenFile();

    int preferred_bytes{SizeConverter::megabytesToBytes(size_limit)};
    bool is_file_too_big{SizeConverter::bytesToMegabytes(logs_file.size()) > size_limit};

    if (is_file_too_big && !Settings::records()->overwriteFullHistoryFile())
    {
        logs_file.seek(logs_file.size() - preferred_bytes);
        QByteArray last_bytes{logs_file.read(preferred_bytes)};
        logs_file.resize(0);
        output_stream << last_bytes;
        output_stream.resetStatus();
        output_stream.reset();
    }

    if (is_file_too_big && Settings::records()->overwriteFullHistoryFile())
        clearLogsFile();
}


bool Logger::validate()
{
    if (!Settings::records()->saveLogsIntoFile())
        return false;

    if (!logs_file.exists())
        reopenFile();

    resizeFileSizeNotWithinRange();

    if (!isWritePossible())
        return false;

    return true;
}


void Logger::writeToStream()
{
    write_mutex.lock();
    output_stream << streamTextResult();
    clearStreamText();
    output_stream.resetStatus();
    output_stream.reset();
    write_mutex.unlock();
}
