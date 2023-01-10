#include "checkcommandparser.h"

#include "outputfilter.h"
#include "logger.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>


CheckCommandParser::CheckCommandParser() :
    line_to_source_map()
{
     line_to_source_map.insert(QString("System"), Package::Source::Repo);
     line_to_source_map.insert(QString("AUR"), Package::Source::AUR);
     line_to_source_map.insert(QString("POLAUR"), Package::Source::POLAUR);
}


QHash<QString, Package::Source> CheckCommandParser::retrieveInfoMap()
{
    QScopedPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->setProcessChannelMode(QProcess::MergedChannels);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -C --noconfirm");
    pacman_qi->waitForStarted();
    pacman_qi->waitForFinished(100000);
    QString output(pacman_qi->readAllStandardOutput());

    Logger::logger()->writeToFile(output, Logger::WriteOperations::CheckUpdates);

    QHash<QString, Package::Source> system_packages{};
    QStringList output_list = output.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
    QString current_source_line = QString();
    QStringListIterator it(output_list);

    while (it.hasNext())
    {
        QString line = it.next();
        QString filtered_line = OutputFilter::filteredOutput(line).simplified();
        bool startsFromDoubleColon = OutputFilter::startsFromDoubleColon(filtered_line);

        if (startsFromDoubleColon)
            current_source_line = OutputFilter::getSourceFromDoubleColon(filtered_line);

        if (startsFromDoubleColon && QString::compare(current_source_line, "Unmerged pacnew/pacsave files") == 0)
        {
            emit pacman_qi.data()->finished(0, QProcess::ExitStatus::NormalExit);
            break;
        }

        if (line.contains("=>"))
           system_packages.insert(filtered_line, line_to_source_map.value(current_source_line));
    }

    return system_packages;
}