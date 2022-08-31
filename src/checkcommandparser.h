#pragma once

#include "commandparser.h"

#include <QTextBrowser>


class CheckCommandParser : public CommandParser
{
public:
    CheckCommandParser(QTextBrowser* new_packages_update_textarea);
    QStringList retrievePackages() override;

private:
    QTextBrowser* packages_update_textarea;
};

