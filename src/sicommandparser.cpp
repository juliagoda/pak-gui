#include "sicommandparser.h"
#include "logger.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>


SiCommandParser::SiCommandParser()
{

}


QStringList SiCommandParser::retrieveInfo()
{
    QScopedPointer<QProcess> pacman_si(new QProcess);
    pacman_si->setProcessChannelMode(QProcess::MergedChannels);
    pacman_si.data()->start("/bin/bash", QStringList() << "-c" << "pak -Si");
    pacman_si.data()->waitForStarted();
    pacman_si->waitForFinished();
    QString output(pacman_si->readAllStandardOutput());
    Logger::logger()->writeToFile(output, Logger::WriteOperations::CheckAvailable);
    return output.split(QRegularExpression("Validated By[^\n]*\n\n"));
}
