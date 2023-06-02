#pragma once

#include "statisticscommandparser.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockStatisticsCommandParser : public StatisticsCommandParser
{
    Q_OBJECT

public:
    explicit MockStatisticsCommandParser() = default;
    friend class TestStatisticsCommandParser;

    QString generateResult() override;
};


class TestStatisticsCommandParser : public QObject
{
    Q_OBJECT

public:
    TestStatisticsCommandParser(QObject* parent = nullptr);

private slots:
    void statisticsActionsAreCorrectlyAddedToList();
    void statisticActionsListIsCorrectlyConvertedToMap();

private:
    MockStatisticsCommandParser statistics_command_parser;
};
