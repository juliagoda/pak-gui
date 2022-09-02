#pragma once

#include "commandparser.h"


class CheckCommandParser : public CommandParser
{
public:
    CheckCommandParser();
    QStringList retrievePackages() override;
};

