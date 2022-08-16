#include "sicommandparser.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>


SiCommandParser::SiCommandParser()
{

}


QStringList SiCommandParser::retrievePackages()
{
    QScopedPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -Si");
    pacman_qi->waitForFinished();
    QString output(pacman_qi->readAllStandardOutput());
    return output.split(QRegularExpression("Validated By[^\n]*\n\n"));
}
