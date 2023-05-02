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
    QStringList output_list{output.split(QRegExp("[\r\n]"), QString::SkipEmptyParts)};
    QStringListIterator it{output_list};
    uint double_colon_line_count{0};

    while (it.hasNext())
    {
        QString line{it.next()};
        QString filtered_line{OutputFilter::filteredOutput(line).simplified()};
        bool starts_from_double_colon{OutputFilter::startsFromDoubleColon(filtered_line)};

        if (starts_from_double_colon)
            double_colon_line_count++;

        if (finishProcessBeforeEnd(starts_from_double_colon, double_colon_line_count))
            break;

        if (line.contains("=>") && !OutputFilter::isCheckWarningLine(filtered_line))
           system_packages.insert(filtered_line, line_to_source_map.value(double_colon_line_count));
    }

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


bool CheckCommandParser::finishProcessBeforeEnd(bool starts_from_double_colon, int double_colon_line_count)
{
    const bool is_unmerged_pacnew_files_line = starts_from_double_colon && double_colon_line_count == 5;
    if (is_unmerged_pacnew_files_line)
    {
        emit pacman_qi.data()->finished(0, QProcess::ExitStatus::NormalExit);
        return true;
    }

    return false;
}
