#pragma once

#include "commandparser.h"

class StatisticsCommandParser : public CommandParser
{
public:
    StatisticsCommandParser();
    QStringList retrieveInfo() override;
};

