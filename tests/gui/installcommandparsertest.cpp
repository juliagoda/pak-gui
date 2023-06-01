#include "installcommandparsertest.h"


MockInstallCommandParser::MockInstallCommandParser() :
    InstallCommandParser()
{
    // ...
}


void MockInstallCommandParser::start(QSharedPointer<Process> &process,
                                     uint packages_to_update)
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
