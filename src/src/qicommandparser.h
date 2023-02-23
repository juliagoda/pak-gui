#pragma once

#include "commandparser.h"


class QiCommandParser : public CommandParser
{
public:
    ~QiCommandParser() override = default;

    QStringList retrieveInfo() override;

protected:
    virtual QString generateResult();
};

