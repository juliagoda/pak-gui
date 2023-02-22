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

    QString generatePakCheckResults() override;
    bool finishProcessBeforeEnd(bool starts_from_double_colon, const QString& current_source_line) override;
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
