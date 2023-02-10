#include "statisticscommandparser.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockStatisticsCommandParser : public StatisticsCommandParser
{
    Q_OBJECT

public:
    explicit MockStatisticsCommandParser();
    friend class TestStatisticsCommandParser;
};




class TestStatisticsCommandParser : public QObject
{
    Q_OBJECT

public:
    TestStatisticsCommandParser(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockStatisticsCommandParser statistics_command_parser;
};
