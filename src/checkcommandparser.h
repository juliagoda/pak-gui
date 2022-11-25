#pragma once

#include "commandparser.h"


class CheckCommandParser : public CommandParser
{
    Q_OBJECT

public:
    CheckCommandParser();
    QStringList retrieveInfo() override;

signals:
    void startOtherThreads();
};

