#include "statisticscommandparser.h"

#include "logger.h"
#include "outputfilter.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>


QStringList StatisticsCommandParser::retrieveInfo()
{
    QScopedPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -L");
    pacman_qi->waitForStarted();
    pacman_qi->waitForFinished();
    QString output = QString::fromUtf8(pacman_qi->readAll());
    Logger::logger()->writeToFile(output, Logger::WriteOperations::ShowStatistics);
    QStringList output_list = output.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
    QStringListIterator it(output_list);
    QStringList result = QStringList();

    while (it.hasNext())
    {
        QString line = it.next().toUtf8();
        if (line.contains("actions:"))
           result.append(OutputFilter::filteredOutput(line));
    }

    return result;
}


QMap<QString, uint> StatisticsCommandParser::convertToMap(QStringList& retrievedInfos)
{
    QMap<QString, uint> retrievedInfoMap;
    for (auto& retrievedInfo : retrievedInfos)
    {
       uint separatorIndex = retrievedInfo.indexOf(":");
       retrievedInfoMap.insert(retrievedInfo.mid(0, separatorIndex).toUtf8(), retrievedInfo.mid(separatorIndex + 1).toUInt());
    }

    return retrievedInfoMap;
}
