#include "qicommandparser.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>


QiCommandParser::QiCommandParser(QTextBrowser* new_packages_uninstallation_textarea) :
    packages_uninstallation_textarea{new_packages_uninstallation_textarea}
{

}


QStringList QiCommandParser::retrievePackages()
{
    QScopedPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -Qi");
    pacman_qi->waitForFinished();
    QString output(pacman_qi->readAllStandardOutput());
    return output.split(QRegularExpression("Validated By[^\n]*\n\n"));
}
