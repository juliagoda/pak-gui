#pragma once

#include "commandparser.h"


class SiCommandParser : public CommandParser
{
public:
    QStringList retrieveInfo() override;
};

