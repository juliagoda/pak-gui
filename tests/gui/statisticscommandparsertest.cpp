#include "statisticscommandparsertest.h"



MockStatisticsCommandParser::MockStatisticsCommandParser() :
    StatisticsCommandParser()
{
    // ...
}


QString MockStatisticsCommandParser::generateResult()
{
    return QString(":: Statistics by month: 2023-02\n"
                   "\n"
                   "Install actions: 34\n"
                   "\n"
                   "Downgrade actions: 20\n"
                   "\n"
                   "Remove actions: 23\n"
                   "\n"
                   "Update actions: 12\n");
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
