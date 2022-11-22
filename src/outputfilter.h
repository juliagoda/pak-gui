#pragma once

#include <QList>
#include <QRegExp>
#include <QStringList>
#include <functional>

class OutputFilter
{
public:
    explicit OutputFilter();
    static QString filteredOutput(QString& text_output);
    static QStringList filteredLines(QStringList& output_lines, std::function<bool(const QString&)> conditional);
    static bool startsFromNumber(const QString& output_line);

private:
    static QList<QRegExp> initializeList();
    static void addToList(QStringList& lines_list, const QString& line);

    static QList<QRegExp> filtersList;
};

