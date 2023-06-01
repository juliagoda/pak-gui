#pragma once

#include "sicommandparser.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockSiCommandParser : public SiCommandParser
{
    Q_OBJECT

public:
    explicit MockSiCommandParser() = default;
    friend class TestAvailablePackagesColumn;

    QString generateResult() override;
};


class TestSiCommandParser : public QObject
{
    Q_OBJECT

public:
    TestSiCommandParser(QObject* parent = nullptr);

private slots:
    void initTestCase_data();
    void isListContainingTwoPackages();
    void isListContainingPackagesWithCorrectContent();

private:
    MockSiCommandParser si_command_parser;
};
