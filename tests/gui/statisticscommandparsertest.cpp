#include "statisticscommandparsertest.h"



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


void TestStatisticsCommandParser::statisticsActionsAreCorrectlyAddedToList()
{
    auto list = statistics_command_parser.retrieveInfo();

    QCOMPARE(list.join("\n"), QString("Install actions: 34\nDowngrade actions: 20\nRemove actions: 23\nUpdate actions: 12"));
}


void TestStatisticsCommandParser::statisticActionsListIsCorrectlyConvertedToMap()
{
    auto list = statistics_command_parser.retrieveInfo();
    auto map = statistics_command_parser.convertToMap(list);

    QCOMPARE(map.value("Install actions"), 34);
    QCOMPARE(map.value("Downgrade actions"), 20);
    QCOMPARE(map.value("Remove actions"), 23);
    QCOMPARE(map.value("Update actions"), 12);
}
