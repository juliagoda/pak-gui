#pragma once

#include "commandparser.h"

class StatisticsCommandParser : public CommandParser
{
public:
    QStringList retrieveInfo() override;
    QMap<QString, uint> convertToMap(QStringList &retrievedInfos);
};

