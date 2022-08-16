#pragma once

#include "commandparser.h"

class QiCommandParser : public CommandParser
{
public:
    QiCommandParser();
    QStringList retrievePackages() override;
};

