#pragma once

#include <QStringList>
#include <QObject>


class CommandParser : public QObject
{
    Q_OBJECT

public:
    virtual ~CommandParser() override = default;
    virtual QStringList retrieveInfo() = 0;
};

