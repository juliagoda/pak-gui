#include "searchallcommandparser.h"
#include "outputfilter.h"
#include "logger.h"

#include <QPointer>


SearchAllCommandParser::SearchAllCommandParser(const QString& new_package_name) :
    package_name(new_package_name),
    packages_lines()
{

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
    QObject::connect(pacman_qi, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [this](int exit_code, QProcess::ExitStatus exit_status){ emit searchEnded(packages_lines); });
    QObject::connect(pacman_qi, &QProcess::errorOccurred, [&pacman_qi](QProcess::ProcessError error) { Logger::logger()->logWarning(QStringLiteral("Error during search: %1").arg(pacman_qi->errorString())); });

    QObject::connect(pacman_qi, &QProcess::readyReadStandardOutput, [=]() mutable
    {
        while (pacman_qi.data()->canReadLine())
        {
            QString line = pacman_qi.data()->readLine();
            auto filtered_line = OutputFilter::filteredOutput(line).remove("\n");
            Logger::logger()->writeLineToFile(filtered_line);

            if (OutputFilter::startsFromDoubleColon(filtered_line))
                current_source_line = OutputFilter::getSourceFromDoubleColon(filtered_line);

            if (OutputFilter::isPackageLine(filtered_line))
            {
                QString appendedSourceToLine(" [" + current_source_line + "]\n");
                packages_lines.append(filtered_line.append(appendedSourceToLine));
            }
        }});

    return QStringList();
}
