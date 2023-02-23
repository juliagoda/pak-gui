#include "qicommandparsertest.h"


MockQiCommandParser::MockQiCommandParser() :
    QiCommandParser()
{
    // ...
}


QString MockQiCommandParser::generateResult()
{
    QString gimp = package_content_gimp;
    return gimp.append("\n").append(package_content_a52dec);
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


