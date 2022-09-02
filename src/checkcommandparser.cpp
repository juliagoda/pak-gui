#include "checkcommandparser.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>


CheckCommandParser::CheckCommandParser()
{

}


QStringList CheckCommandParser::retrievePackages()
{
    QScopedPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -C");
    pacman_qi->waitForFinished();
    QString output(pacman_qi->readAllStandardOutput());

    QStringList system_packages = QStringList();
    QStringList output_list = output.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
    QStringListIterator it(output_list);

    while (it.hasNext())
    {
        QString line = it.next();
        if (line.contains("=>"))
        {
           system_packages.append(line.simplified());
        }
    }

    return system_packages;
}
