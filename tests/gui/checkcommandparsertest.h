#pragma once

#include "checkcommandparser.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockCheckCommandParser : public CheckCommandParser
{
    Q_OBJECT

public:
    explicit MockCheckCommandParser() = default;
    ~MockCheckCommandParser() override = default;
    friend class TestCheckCommandParser;

    QString generatePakCheckResults() override;
    bool finishProcessBeforeEnd(bool starts_from_double_colon, int double_colon_line_count) override;
};



class TestCheckCommandParser : public QObject
{
    Q_OBJECT

public:
    TestCheckCommandParser(QObject* parent = nullptr);

private slots:
    void retrievedPackagesMapCountIsEqualToThree();
    void retrievedPackagesMapContainsAclPackagesFromRepo();
    void retrievedPackagesMapContainsKonsolePackageFromPolaur();
    void unmergedPacsaveFilesLineTriggersProcessExit();

private:
    MockCheckCommandParser check_command_parser;
};
