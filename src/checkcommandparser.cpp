#include "checkcommandparser.h"
#include "outputfilter.h"
#include "logger.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>

CheckCommandParser::CheckCommandParser()
{

}


QStringList CheckCommandParser::retrieveInfo()
{
    QScopedPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->setProcessChannelMode(QProcess::MergedChannels);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -C --noconfirm");
    pacman_qi->waitForStarted();
    pacman_qi->waitForFinished(100000);
    QString output(pacman_qi->readAllStandardOutput());

    Logger::logger()->writeToFile(output, Logger::WriteOperations::CheckUpdates);

    QStringList system_packages = QStringList();
    QStringList output_list = output.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
    QStringListIterator it(output_list);

    emit startOtherThreads();

    while (it.hasNext())
    {
        QString line = it.next();
        if (line.contains("=>"))
        {
           system_packages.append(OutputFilter::filteredOutput(line).simplified());
        }
    }

    return system_packages;
}
