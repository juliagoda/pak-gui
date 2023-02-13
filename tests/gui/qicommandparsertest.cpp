#include "qicommandparsertest.h"


MockQiCommandParser::MockQiCommandParser() :
    QiCommandParser()
{
  // ...
}


TestQiCommandParser::TestQiCommandParser(QObject* parent) :
    QObject(parent),
    qi_command_parser()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestQiCommandParser::cleanup()
{
  // ...
}


