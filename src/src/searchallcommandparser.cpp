#include "searchallcommandparser.h"

#include "outputfilter.h"
#include "logger.h"

#include <QPointer>


SearchAllCommandParser::SearchAllCommandParser(const QString& new_package_name) :
    package_name(new_package_name),
    packages_lines()
{
   // ...
}


QStringList SearchAllCommandParser::retrieveInfo()
{
    packages_lines.clear();
    QString current_source_line = QString();
    QPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->setProcessChannelMode(QProcess::MergedChannels);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -SS " + package_name);
    pacman_qi->waitForStarted();

    Logger::logger()->logInfo(QStringLiteral("Trying search package: %1 everywhere").arg(package_name));
    Logger::logger()->writeSectionToFile(Logger::WriteOperations::SearchAll);
    QObject::connect(pacman_qi, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &SearchAllCommandParser::finishProcess);
    QObject::connect(pacman_qi, &QProcess::errorOccurred, [&pacman_qi, this](QProcess::ProcessError /*error*/) { showError(pacman_qi->errorString()); });

    QObject::connect(pacman_qi, &QProcess::readyReadStandardOutput, [pacman_qi, current_source_line, this]() mutable
    {
        while (pacman_qi.data()->canReadLine())
        {
            QString line = pacman_qi.data()->readLine();
            processReadLine(line, current_source_line);
        }});

    return QStringList();
}


void SearchAllCommandParser::finishProcess(int /*exit_code*/, QProcess::ExitStatus /*exit_status*/)
{
    Logger::logger()->logInfo(QStringLiteral("Found %1 sources during package search").arg(packages_lines.count()));
    emit searchEnded(packages_lines);
}


void SearchAllCommandParser::showError(const QString& errorString)
{
    Logger::logger()->logFatal(QStringLiteral("Error during search: %1").arg(errorString));
}


void SearchAllCommandParser::processReadLine(QString& line, QString& current_source_line)
{
    auto filtered_line = OutputFilter::filteredOutput(line).remove("\n");
    Logger::logger()->writeLineToFile(filtered_line);

    if (OutputFilter::startsFromDoubleColon(filtered_line))
        current_source_line = OutputFilter::getSourceFromDoubleColon(filtered_line);

    if (OutputFilter::isPackageLine(filtered_line))
    {
        QString appendedSourceToLine(" [" + current_source_line + "]\n");
        packages_lines.append(filtered_line.append(appendedSourceToLine));
    }
}
