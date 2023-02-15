#pragma once

#include "commandparser.h"
#include "qobjectdefs.h"

#include <QProcess>
#include <QString>
#include <QStringList>
#include <QRegularExpression>


class SearchAllCommandParser : public CommandParser
{
    Q_OBJECT

public:
    SearchAllCommandParser(const QString& new_package_name);
    ~SearchAllCommandParser() override = default;

    QStringList retrieveInfo() override;

signals:
    void searchEnded(QStringList results);

private:
    QString package_name;
    QStringList packages_lines;
};

