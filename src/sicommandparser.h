#pragma once

#include "commandparser.h"


class SiCommandParser : public CommandParser
{
public:
    SiCommandParser();
    QStringList retrieveInfo() override;
};

