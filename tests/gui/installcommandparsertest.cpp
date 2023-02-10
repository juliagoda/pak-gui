#include "installcommandparsertest.h"


MockInstallCommandParser::MockInstallCommandParser() :
    InstallCommandParser()
{
    // ...
}




TestInstallCommandParser::TestInstallCommandParser(QObject* parent) :
    QObject(parent),
    install_command_parser()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestInstallCommandParser::cleanup()
{
    // ...
}
