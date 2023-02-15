#pragma once

#include <QList>
#include <QRegExp>
#include <QStringList>
#include <functional>

class OutputFilter
{
public:
    explicit OutputFilter() = default;
    virtual ~OutputFilter() = default;

    static QString filteredOutput(QString& text_output);
    static QString getSourceFromDoubleColon(QString& output_line);
    static QString getSourceFromSearchLine(QString& output_line);
    static QString getPackageFromSearchLine(QString& output_line);
    static QStringList filteredLines(QStringList& output_lines, std::function<bool(const QString&)> conditional);
    static bool startsFromNumber(const QString& output_line);
    static bool startsFromDoubleColon(const QString& output_line);
    static bool isPackageLine(const QString& output_line);

private:
    static QList<QRegExp> initializeList();
    static void addToList(QStringList& lines_list, const QString& line);

    static QList<QRegExp> filtersList;
};

