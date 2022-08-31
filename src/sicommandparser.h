#pragma once

#include "commandparser.h"

#include <QTextBrowser>

class SiCommandParser : public CommandParser
{
public:
    SiCommandParser(QTextBrowser* new_packages_installation_textarea);
    QStringList retrievePackages() override;

private:
    QTextBrowser* packages_installation_textarea;
};

