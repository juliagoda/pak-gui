#include "logger.h"

#include "outputfilter.h"
#include "defs.h"
#include "pakGuiSettings.h"

#include <QDebug>
#include <QMetaEnum>


Logger* Logger::instance{nullptr};
QMutex Logger::instance_mutex;
QMutex Logger::write_mutex;


Logger::Logger() :
    logs_file(Converter::fullConfigPath()),
    output_stream()
{
    reopenFile();
}


Logger::~Logger()
{
    closeOnQuit();
}


Logger* Logger::logger()
{
    instance_mutex.lock();
    if (instance == nullptr)
        instance = new Logger();

    instance_mutex.unlock();
    return instance;
}


void Logger::writeToFile(QString& text, WriteOperations section)
{
    if (!pakGuiSettings::save_logs_into_file())
        return;

    if (!logs_file.exists())
        reopenFile();

    write_mutex.lock();
    resizeFileSizeNotWithinRange();

    if (isWritePossible())
    {
        appendSection(section);
        appendNewLine();
        output_stream << OutputFilter::filteredOutput(text);
        appendNewLine();
        appendSeparator();
        appendNewLine();
        appendNewLine();
    }

    write_mutex.unlock();
}


void Logger::logInfo(const QString &text)
{
    if (pakGuiSettings::hide_info_logs())
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
    if (!pakGuiSettings::show_debug())
        return;

    logIntoFile(QString("DEBUG"), text);
    qDebug() << "[DEBUG] " << text;
}


void Logger::appendSection(WriteOperations section)
{
    QString section_text = QVariant::fromValue(section).toString();
    QString local_time = QDateTime::currentDateTime().toLocalTime().toString();
    QString line = QString("\n\n\n---------------[").append(section_text.toUpper()).append(QString("]---------------"));
    output_stream << local_time;
    output_stream << line;
}


void Logger::appendSeparator()
{
    output_stream << QString("////////////////////////////////////////////////////////////");
}


void Logger::appendNewLine()
{
    output_stream << QString("\n\n");
}


void Logger::logIntoFile(const QString& section, const QString& text)
{
    if (!logs_file.exists())
        reopenFile();

    write_mutex.lock();
    resizeFileSizeNotWithinRange();

    QString local_time = QDateTime::currentDateTime().toLocalTime().toString();
    QString local_text = text;
    if (pakGuiSettings::save_logs_into_file())
        output_stream << " [" << section << "]  " << OutputFilter::filteredOutput(local_text) << "  (" << local_time << ")\n";

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

    instance_mutex.unlock();
}


void Logger::reopenFile()
{
    if (logs_file.isOpen())
        logs_file.close();

    logs_file.open(QIODevice::WriteOnly | QIODevice::Append);
    output_stream.setDevice(&logs_file);
    if (logs_file.isOpen())
        logInfo(QStringLiteral("Logs file \"%1\" successfully opened\n").arg(logs_file.fileName()));
}


void Logger::resizeFileSizeNotWithinRange()
{
    int size_limit = pakGuiSettings::history_file_size_limit_in_Mb();
   if (size_limit == 0)
       return;

   if (Converter::bytesToMegabytes(logs_file.size()) > size_limit)
       logs_file.resize(Converter::megabytesToBytes(size_limit));
}
