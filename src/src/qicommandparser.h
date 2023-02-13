#pragma once

#include "commandparser.h"


class QiCommandParser : public CommandParser
{
public:
    virtual ~QiCommandParser() override = default;
    QStringList retrieveInfo() override;
};

