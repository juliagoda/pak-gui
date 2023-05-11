#include "sicommandparser.h"

#include "logger.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>


QStringList SiCommandParser::retrieveInfo()
{
    QString output = generateResult();
    Logger::logger()->writeToFile(output, Logger::WriteOperations::CheckAvailable);
    static QRegularExpression new_lines_expression("\n\n");
    auto list = output.split(new_lines_expression);
    if (list.last().trimmed().isEmpty())
        list.pop_back();

    return list;
}


QString SiCommandParser::generateResult()
{
    QScopedPointer<QProcess> pacman_si(new QProcess);
    pacman_si->setProcessChannelMode(QProcess::MergedChannels);
    pacman_si.data()->start("/bin/bash", QStringList() << "-c" << "pak -Si");
    pacman_si.data()->waitForStarted();
    pacman_si->waitForFinished();
    return pacman_si->readAllStandardOutput();
}
