#pragma once

#include "commandparser.h"
#include "package.h"

#include <QHash>


class CheckCommandParser : public CommandParser
{
    Q_OBJECT

public:
    CheckCommandParser();
    QStringList retrieveInfo() override { return QStringList(); };
    QHash<QString, Package::Source> retrieveInfoMap();

signals:
    void startOtherThreads();

private:
    QHash<QString, Package::Source> line_to_source_map;
};

