#include "qicommandparser.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>


QiCommandParser::QiCommandParser()
{

}


QStringList QiCommandParser::retrieveInfo()
{
    QScopedPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -Qi");
    pacman_qi->waitForStarted();
    pacman_qi->waitForFinished(15000);
    QString output(pacman_qi->readAllStandardOutput());
    return output.split(QRegularExpression("Validated By[^\n]*\n\n"));
}
