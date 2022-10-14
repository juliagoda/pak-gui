#include "downloadcommandparser.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>

DownloadCommandParser::DownloadCommandParser()
{

}

QStringList DownloadCommandParser::retrieveInfo()
{
    QScopedPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "0 | pak -G gimp");
    pacman_qi->waitForFinished(3000);
    QString output(pacman_qi->readAllStandardOutput());
    return output.split(QRegularExpression("(([0-9]+\s.*\/)|(\s?[0-9]+\.\s[\w-]+)){1}"));
}
