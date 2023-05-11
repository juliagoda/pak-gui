#include "outputfilter.h"

#include <QFuture>
#include <QRegExp>
#include <QtConcurrent/QtConcurrent>


QList<QRegExp> OutputFilter::filtersList = initializeList();


QString OutputFilter::filteredOutput(QString& text_output)
{
    QList<QRegExp>::iterator filters_it;
    for (filters_it = filtersList.begin(); filters_it != filtersList.end(); filters_it++)
        text_output.remove(*filters_it);

    return text_output;
}


QStringList OutputFilter::filteredOutputFromInstalledPackages(const QStringList& text_output)
{
    QStringList output_list;
    QStringList::const_iterator list_it;
    static QRegularExpression tag{"\\[.*\\]"};
    for (list_it = text_output.begin(); list_it != text_output.end(); list_it++)
    {
        QString list_el = *list_it;
        if (list_el.count(tag) == 1)
            output_list.append(list_el.trimmed());
    }

    return output_list;
}


QString OutputFilter::getSourceFromDoubleColon(QString& output_line)
{
    return output_line.remove(QString("::")).trimmed();
}


QString OutputFilter::getSourceFromSearchLine(QString& output_line)
{
    static QRegularExpression regex(".*\\[(.*)\\].*");
    return regex.match(output_line).captured(1);
}


QString OutputFilter::getPackageFromSearchLine(QString& output_line)
{
    static QRegularExpression regex("^(\\S*)\\s*\\S*");
    return regex.match(output_line).captured(1);
}


void OutputFilter::addToList(QStringList& lines_list, const QString& line)
{
    lines_list.append(line);
}


QStringList OutputFilter::filteredLines(QStringList& output_lines, std::function<bool (const QString&)> conditional)
{
    QFuture<QStringList> filtered_strings = QtConcurrent::filteredReduced(output_lines, conditional, addToList);
    return filtered_strings.result();
}


QList<QRegExp> OutputFilter::initializeList()
{
    QList<QRegExp> filters;
    filters.append(QRegExp("\u001B"));
    filters.append(QRegExp("\\[[0-9]{2}m"));
    filters.append(QRegExp("\\[0m"));
    filters.append(QRegExp("\\[1;[0-9]{2}m"));
    filters.append(QRegExp(""));
    filters.append(QRegExp("\\[?25l"));
    filters.append(QRegExp("\\[\\?"));
    filters.append(QRegExp("\\[[0-9]{1}F "));
    filters.append(QRegExp("\\[1E"));

    return filters;
}


bool OutputFilter::startsFromNumber(const QString& output_line)
{
    return output_line.contains(QRegExp("^\\s*[0-9]+\\.?\\s+"));
}


bool OutputFilter::startsFromDoubleColon(const QString& output_line)
{
    return output_line.startsWith(QString(":: "));
}


bool OutputFilter::isPackageLine(const QString &output_line)
{
    return output_line.contains(QRegExp("^.*/\\S+\\s+\\d+\\.\\d+.\\d+.*"));
}


bool OutputFilter::isCheckWarningLine(const QString& output_line)
{
    return output_line.count(':') >= 2 && output_line.contains(QRegExp("\\(.*=>.*\\)"));
}


