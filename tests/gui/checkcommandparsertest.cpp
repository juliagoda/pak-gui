 #include "checkcommandparsertest.h"


MockCheckCommandParser::MockCheckCommandParser() :
    CheckCommandParser()
{

}



TestCheckCommandParser::TestCheckCommandParser(QObject* parent) :
    QObject(parent),
    check_command_parser()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestCheckCommandParser::cleanup()
{

}
