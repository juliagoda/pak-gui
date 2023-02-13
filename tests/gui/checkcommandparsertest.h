#pragma once

#include "checkcommandparser.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockCheckCommandParser : public CheckCommandParser
{
    Q_OBJECT

public:
    explicit MockCheckCommandParser();
    friend class TestCheckCommandParser;
};



class TestCheckCommandParser : public QObject
{
    Q_OBJECT

public:
    TestCheckCommandParser(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockCheckCommandParser check_command_parser;
};
