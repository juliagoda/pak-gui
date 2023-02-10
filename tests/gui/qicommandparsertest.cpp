#include "qicommandparsertest.h"



MockQiCommandParser::MockQiCommandParser(QWidget* new_parent) :
    QiCommandParser(new_parent)
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
