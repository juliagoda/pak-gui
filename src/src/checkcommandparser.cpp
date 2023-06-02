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
     line_to_source_map.insert(2, Package::Source::Repo);
     line_to_source_map.insert(3, Package::Source::AUR);
     line_to_source_map.insert(4, Package::Source::POLAUR);
}


QHash<QString, Package::Source> CheckCommandParser::retrieveInfoMap()
{
    QString output{generatePakCheckResults()};

    Logger::logger()->writeToFile(output, Logger::WriteOperations::CheckUpdates);

    QHash<QString, Package::Source> system_packages;
    QStringList output_list{output.split(QRegExp("[\r\n]"), Qt::SkipEmptyParts)};
    QStringListIterator it{output_list};
    processLines(system_packages, it);

    return system_packages;
}


QString CheckCommandParser::generatePakCheckResults()
{
    pacman_qi.reset(new QProcess);
    pacman_qi->setProcessChannelMode(QProcess::MergedChannels);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -C --noconfirm");
    pacman_qi->waitForStarted();
    pacman_qi->waitForFinished();
    return pacman_qi->readAllStandardOutput();
}


void CheckCommandParser::processLines(QHash<QString, Package::Source>& system_packages,
                                      QStringListIterator& iterator)
{
    uint double_colon_line_count{0};

    while (iterator.hasNext())
    {
        QString line{iterator.next()};
        QString filtered_line{OutputFilter::filteredOutput(line).simplified()};
        increaseDoubleColonCounter(filtered_line, double_colon_line_count);
        appendPackageLine(system_packages, filtered_line, double_colon_line_count);
    }
}


void CheckCommandParser::increaseDoubleColonCounter(const QString& filtered_line, uint &counter)
{
    bool starts_from_double_colon{OutputFilter::startsFromDoubleColon(filtered_line)};

    if (starts_from_double_colon)
        counter++;
}


void CheckCommandParser::appendPackageLine(QHash<QString, Package::Source>& system_packages,
                                           const QString& filtered_line, uint& counter)
{
    if (filtered_line.contains("=>") && !OutputFilter::isCheckWarningLine(filtered_line))
        system_packages.insert(filtered_line, line_to_source_map.value(counter));
}
