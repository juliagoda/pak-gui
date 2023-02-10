#include "statisticscommandparsertest.h"



MockStatisticsCommandParser::MockStatisticsCommandParser() :
    StatisticsCommandParser()
{
  // ...
}



TestStatisticsCommandParser::TestStatisticsCommandParser(QObject* parent) :
    QObject(parent),
    statistics_command_parser()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestStatisticsCommandParser::cleanup()
{
  // ...
}
