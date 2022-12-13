#include "qicommandparser.h"

#include "logger.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>


QStringList QiCommandParser::retrieveInfo()
{
    QScopedPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->setProcessChannelMode(QProcess::MergedChannels);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -Qi");
    pacman_qi->waitForStarted();
    pacman_qi->waitForFinished();
    QString output(pacman_qi->readAllStandardOutput());
    Logger::logger()->writeToFile(output, Logger::WriteOperations::CheckInstalled);
    return output.split(QRegularExpression("Validated By[^\n]*\n\n"));
}
