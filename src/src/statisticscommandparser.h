#pragma once

#include "commandparser.h"

class StatisticsCommandParser : public CommandParser
{
public:
    ~StatisticsCommandParser() override = default;

    QStringList retrieveInfo() override;
    QMap<QString, uint> convertToMap(QStringList &retrievedInfos);
};

