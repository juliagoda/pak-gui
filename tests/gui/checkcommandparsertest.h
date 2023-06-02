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

private:
    MockCheckCommandParser check_command_parser;
};
