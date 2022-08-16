#pragma once

#include <QStringList>

class CommandParser
{
public:
    virtual ~CommandParser() = default;
    virtual QStringList retrievePackages() = 0;
};

