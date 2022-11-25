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
    if (logs_file.open(QIODevice::WriteOnly | QIODevice::Append))
        qInfo() << "Opened logs file \"" << logs_file.fileName() << "\" successfully";

    output_stream.setDevice(&logs_file);
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

    write_mutex.lock();

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
    qInfo() << text;
}


void Logger::logWarning(const QString &text)
{
    logIntoFile(QString("WARNING"), text);
    qWarning() << text;
}


void Logger::logFatal(const QString &text)
{
    logIntoFile(QString("FATAL"), text);
    qCritical() << text;
}


void Logger::logDebug(const QString &text)
{
    if (!pakGuiSettings::show_debug())
        return;

    logIntoFile(QString("DEBUG"), text);
    qDebug() << text;
}


void Logger::appendSection(WriteOperations section)
{
    QString section_text = QVariant::fromValue(section).toString();
    QString local_time = QDateTime::currentDateTime().toLocalTime().toString();
    QString line = QString("---------------[").append(local_time + " - " + section_text.toUpper()).append(QString("]---------------"));
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
    QString local_time = QDateTime::currentDateTime().toLocalTime().toString();
    QString local_text = text;
    if (pakGuiSettings::save_logs_into_file())
       output_stream << local_time << " [" << section << "]  " << OutputFilter::filteredOutput(local_text);
}


bool Logger::isWritePossible()
{
    if (logs_file.exists() && logs_file.isOpen() && logs_file.isWritable())
        return true;

    qWarning() << "Cannot write to file \"" << logs_file.fileName() << "\" - file is not opened or "
                  "you don't have permissions to write into or even doesn't exist";
    return false;
}


void Logger::closeOnQuit()
{
    if (logs_file.isOpen())
        logs_file.close();

    if (logs_file.isOpen())
        qWarning() << "Logs file \"" << logs_file.fileName() << "\" couldn't be properly closed!";

    instance_mutex.unlock();
}
