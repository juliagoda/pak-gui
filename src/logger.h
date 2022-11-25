#pragma once

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
        CheckInstalled
    };
    Q_ENUM(WriteOperations)

    static Logger* logger();
    ~Logger();
    Logger(Logger& instance) = delete;
    void operator=(const Logger& instance) = delete;
    void writeToFile(QString& text, WriteOperations section);

private:
    explicit Logger();

    void appendSection(QTextStream& out, WriteOperations section);
    void appendSeparator(QTextStream& out);
    void appendNewLine(QTextStream& out);
    bool isWritePossible();

    QFile logs_file;
    static Logger* instance;
    static QMutex instance_mutex;
    static QMutex write_mutex;
};

