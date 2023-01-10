#pragma once

#include "commandparser.h"


class QiCommandParser : public CommandParser
{
public:
    QStringList retrieveInfo() override;
};

