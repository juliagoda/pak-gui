#include "sicommandparsertest.h"



MockSiCommandParser::MockSiCommandParser() :
    SiCommandParser()
{
    // ...
}


QString MockSiCommandParser::generateResult()
{
   QString a52dec = package_content_a52dec_si;
   return a52dec.append("\n").append(package_content_alsa_utils_si);
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
