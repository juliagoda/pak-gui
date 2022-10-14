#pragma once

#include "commandparser.h"

class DownloadCommandParser : public CommandParser
{
public:
    DownloadCommandParser();
    QStringList retrieveInfo() override;
};

