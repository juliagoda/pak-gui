#include "sicommandparser.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>


SiCommandParser::SiCommandParser(QTextBrowser* new_packages_installation_textarea) :
    packages_installation_textarea{new_packages_installation_textarea}
{

}


QStringList SiCommandParser::retrievePackages()
{
    QScopedPointer<QProcess> pacman_qi(new QProcess);
    QObject::connect(pacman_qi.data(), &QProcess::readyReadStandardOutput, [=]() { packages_installation_textarea->setText("example"); });
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -Si");
    pacman_qi->waitForFinished();
    QString output(pacman_qi->readAllStandardOutput());
    return output.split(QRegularExpression("Validated By[^\n]*\n\n"));
}
