#pragma once

#include "commandparser.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>

class SearchAllCommandParser : public CommandParser
{
public:
    SearchAllCommandParser(const QString& new_package_name);
    QStringList retrieveInfo() override;

private:
    QString package_name;
};

