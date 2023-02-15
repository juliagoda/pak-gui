#pragma once

#include "commandparser.h"


class SiCommandParser : public CommandParser
{
public:
    ~SiCommandParser() override = default;

    QStringList retrieveInfo() override;
};

