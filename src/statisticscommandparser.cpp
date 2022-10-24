#include "statisticscommandparser.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>
#include <QTextDecoder>

StatisticsCommandParser::StatisticsCommandParser()
{

}

QStringList StatisticsCommandParser::retrieveInfo()
{
    QScopedPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -L");
    pacman_qi->waitForFinished();
    QString output = QString::fromUtf8(pacman_qi->readAll());
    QStringList output_list = output.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
    QStringListIterator it(output_list);
    QStringList result = QStringList();

    while (it.hasNext())
    {
        QString line = it.next().toUtf8();
        if (line.contains("actions:"))
        {
           QString trimmedLeft = line.remove(QString("\033[1;39m"));
           QString trimmedRight = trimmedLeft.remove(QString("\033[0m "));
           result.append(trimmedRight);
        }
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
