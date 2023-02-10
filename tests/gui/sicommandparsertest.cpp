#include "sicommandparsertest.h"



MockSiCommandParser::MockSiCommandParser() :
    SiCommandParser()
{
   // ...
}



TestSiCommandParser::TestSiCommandParser(QObject* parent) :
    QObject(parent),
    si_command_parser()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestSiCommandParser::cleanup()
{
  // ...
}
