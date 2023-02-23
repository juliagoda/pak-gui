#pragma once

#include "sicommandparser.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockSiCommandParser : public SiCommandParser
{
    Q_OBJECT

public:
    explicit MockSiCommandParser();
    friend class TestAvailablePackagesColumn;

    QString generateResult() override;
};



class TestSiCommandParser : public QObject
{
    Q_OBJECT

public:
    TestSiCommandParser(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockSiCommandParser si_command_parser;
};
