#pragma once

#include "qicommandparser.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockQiCommandParser : public QiCommandParser
{
public:
    MockQiCommandParser() = default;
    friend class TestQiCommandParser;

    QString generateResult() override;
};



class TestQiCommandParser : public QObject
{
    Q_OBJECT

public:
    TestQiCommandParser(QObject* parent = nullptr);

private slots:
    void initTestCase_data();
    void isListContainingTwoPackages();
    void isListContainingPackagesWithCorrectContent();

private:
    MockQiCommandParser qi_command_parser;
};
