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
}


const QString& Logger::streamTextResult() const
{
    return stream_text;
}


Logger::~Logger()
{
    closeOnQuit();
}


Logger* Logger::logger()
{
    if (instance == nullptr)
        instance = new Logger();

    return instance;
}


void Logger::writeToFile(QString& text, WriteOperations section)
{
    appendSection(section);
    appendNewLine();
    stream_text += OutputFilter::filteredOutput(text);
    appendNewLine();
    appendSeparator();
    appendNewLine();
    appendNewLine();

#ifdef RUN_TESTS
    return;
#endif

    if (!validate())
        return;

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
        return;

    writeToStream();
}


void Logger::writeLineToFile(QString& line)
{
    stream_text += OutputFilter::filteredOutput(line);
    appendNewLine();

#ifdef RUN_TESTS
    return;
#endif

    writeToStream();
}


void Logger::logInfo(const QString &text)
{
    if (Settings::records()->hideInfoLogs())
        return;

    logIntoFile(QString("INFO"), text);
    qInfo() << "[INFO] " << text;
}


void Logger::logWarning(const QString &text)
{
    logIntoFile(QString("WARNING"), text);
    qWarning() << "[WARNING] " << text;
}


void Logger::logFatal(const QString &text)
{
    logIntoFile(QString("FATAL"), text);
    qCritical() << "[FATAL] " << text;
}


void Logger::logDebug(const QString &text)
{
    if (!Settings::records()->showDebug())
        return;

    logIntoFile(QString("DEBUG"), text);
    qDebug() << "[DEBUG] " << text;
}


void Logger::clearLogsFile()
{
#ifdef RUN_TESTS
    return;
#endif

    Logger::logger()->logInfo(QStringLiteral("Clear logs file - %1").arg(QDateTime::currentDateTime().toString()));

    if (!logs_file.resize(0))
        logWarning(QStringLiteral("Logs file couldn't be removed: %1").arg(logs_file.errorString()));
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
    QString local_text{text};
    stream_text += " [" + section + "]  " + OutputFilter::filteredOutput(local_text) + "  (" + local_time + ")\n";

#ifdef RUN_TESTS
    return;
#endif

    if (!Settings::records()->saveLogsIntoFile())
        return;

    if (!logs_file.exists())
        reopenFile();

    write_mutex.lock();
    resizeFileSizeNotWithinRange();
    output_stream << streamTextResult();
    clearStreamText();
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
    if (logs_file.isOpen())
        logs_file.close();

    if (logs_file.isOpen())
        logWarning(QStringLiteral("Logs file \"%1\" couldn't be properly closed!").arg(logs_file.fileName()));
}


void Logger::reopenFile()
{
#ifdef RUN_TESTS
    return;
#endif

    if (logs_file.isOpen())
        logs_file.close();

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

    int preferredBytes{SizeConverter::megabytesToBytes(size_limit)};
    bool is_file_too_big{SizeConverter::bytesToMegabytes(logs_file.size()) > size_limit};

    if (is_file_too_big && !Settings::records()->overwriteFullHistoryFile())
    {
        logs_file.seek(logs_file.size() - preferredBytes);
        QByteArray last_bytes{logs_file.read(preferredBytes)};
        logs_file.resize(0);
        output_stream << last_bytes;
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
    write_mutex.unlock();
}
