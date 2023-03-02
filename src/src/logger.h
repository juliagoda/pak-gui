#pragma once

#include "pathconverter.h"

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
    QString stream_text;
    QTextStream output_stream;
    static Logger* instance;
    static QMutex write_mutex;
};

