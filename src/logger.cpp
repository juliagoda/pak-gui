#include "logger.h"

#include "outputfilter.h"
#include "defs.h"

#include <QDebug>
#include <QMetaEnum>


Logger* Logger::instance{nullptr};
QMutex Logger::instance_mutex;
QMutex Logger::write_mutex;


Logger::Logger() :
    logs_file(Converter::fullConfigPath())
{
    logs_file.open(QIODevice::WriteOnly | QIODevice::Append);
}


Logger::~Logger()
{
    if (logs_file.isOpen())
        logs_file.close();

    instance_mutex.unlock();
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
    write_mutex.lock();

    if (isWritePossible())
    {
        QTextStream out(&logs_file);
        appendSection(out, section);
        appendNewLine(out);
        out << OutputFilter::filteredOutput(text);
        appendNewLine(out);
        appendSeparator(out);
    }

    write_mutex.unlock();
}


void Logger::appendSection(QTextStream& out, WriteOperations section)
{
    QString section_text = QVariant::fromValue(section).toString();
    QString local_time = QDateTime::currentDateTime().toLocalTime().toString();
    QString line = QString("---------------[").append(local_time + " - " + section_text.toUpper()).append(QString("]---------------"));
    out << line;
}


void Logger::appendSeparator(QTextStream& out)
{
   out << QString("////////////////////////////////////////////////////////////");
}


void Logger::appendNewLine(QTextStream& out)
{
   out << QString("\n\n");
}


bool Logger::isWritePossible()
{
    if (logs_file.exists() && logs_file.isOpen() && logs_file.isWritable())
        return true;

    qWarning() << "Cannot write to file \"" << logs_file.fileName() << "\" - file is not opened or "
                  "you don't have permissions to write into or even doesn't exist";
    return false;
}
