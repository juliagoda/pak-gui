#pragma once

#include "qicommandparser.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockQiCommandParser : public QiCommandParser
{
public:
    MockQiCommandParser();
    friend class TestQiCommandParser;

    QString generateResult() override;
};



class TestQiCommandParser : public QObject
{
    Q_OBJECT

public:
    TestQiCommandParser(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockQiCommandParser qi_command_parser;
};
