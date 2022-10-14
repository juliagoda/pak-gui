#include "statisticscommandparser.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>

StatisticsCommandParser::StatisticsCommandParser()
{

}

QStringList StatisticsCommandParser::retrieveInfo()
{
    QScopedPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -L");
    pacman_qi->waitForFinished();
    QString output(pacman_qi->readAllStandardOutput());
    return output.split(QRegularExpression("actions: [0-9]+"));
}
