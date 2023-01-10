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
        CheckInstalled,
        ShowStatistics,
        MirrorsUpdate,
        UpdateInstalled,
        PrintVCSPackages,
        SearchAll
    };
    Q_ENUM(WriteOperations)

    static Logger* logger();
    virtual ~Logger();
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

private:
    explicit Logger();

    void appendSection(WriteOperations section);
    void appendSeparator();
    void appendNewLine();
    void logIntoFile(const QString& section, const QString& text);
    bool isWritePossible();
    void closeOnQuit();
    void resizeFileSizeNotWithinRange();
    bool validate();

    QFile logs_file;
    QTextStream output_stream;
    static Logger* instance;
    static QMutex instance_mutex;
    static QMutex write_mutex;
};

