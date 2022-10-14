#pragma once

#include <QStringList>
#include <QObject>


class CommandParser
{
public:
    virtual ~CommandParser() = default;
    virtual QStringList retrieveInfo() = 0;
};

