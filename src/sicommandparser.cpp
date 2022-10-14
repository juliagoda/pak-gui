#include "sicommandparser.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>


SiCommandParser::SiCommandParser()
{

}


QStringList SiCommandParser::retrieveInfo()
{
    QScopedPointer<QProcess> pacman_si(new QProcess);
    pacman_si.data()->start("/bin/bash", QStringList() << "-c" << "pak -Si");
    pacman_si->waitForFinished();
    QString output(pacman_si->readAllStandardOutput());
    return output.split(QRegularExpression("Validated By[^\n]*\n\n"));
}
