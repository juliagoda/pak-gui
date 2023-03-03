#include "statisticscommandparser.h"

#include "logger.h"
#include "outputfilter.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>


QStringList StatisticsCommandParser::retrieveInfo()
{
    QString output = generateResult();
    Logger::logger()->writeToFile(output, Logger::WriteOperations::ShowStatistics);
    QStringList output_list = output.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
    QStringListIterator it(output_list);
    QStringList result = QStringList();

    while (it.hasNext())
    {
        QString line{it.next().toUtf8()};
        QString filtered_line = OutputFilter::filteredOutput(line);
        QRegExp action_regex{"^[\\w+\\s+]+:\\s+\\d+"};
        if (action_regex.exactMatch(filtered_line))
           result.append(filtered_line);
    }

    return result;
}


QString StatisticsCommandParser::generateResult()
{
    QScopedPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -L");
    pacman_qi->waitForStarted();
    pacman_qi->waitForFinished();
    return QString::fromUtf8(pacman_qi->readAll());
}


QMap<QString, uint> StatisticsCommandParser::convertToMap(QStringList& retrievedInfos)
{
    QMap<QString, uint> retrievedInfoMap;
    for (auto& retrievedInfo : retrievedInfos)
    {
       uint separatorIndex = retrievedInfo.indexOf(":");
       retrievedInfoMap.insert(retrievedInfo.mid(0, separatorIndex).toUtf8(), retrievedInfo.midRef(separatorIndex + 1).toUInt());
    }

    return retrievedInfoMap;
}
