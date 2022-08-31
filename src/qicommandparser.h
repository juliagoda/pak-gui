#pragma once

#include "commandparser.h"

#include <QTextBrowser>

class QiCommandParser : public CommandParser
{
public:
    QiCommandParser(QTextBrowser* new_packages_uninstallation_textarea);
    QStringList retrievePackages() override;

private:
    QTextBrowser* packages_uninstallation_textarea;
};

