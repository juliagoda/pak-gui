#pragma once

#include "downloadcommandparser.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockDownloadCommandParser : public DownloadCommandParser
{
    Q_OBJECT

public:
    explicit MockDownloadCommandParser(const QString& new_package_name, QWidget* new_parent);
    friend class TestDownloadCommandParser;

    void start() override;
    void inputAnswer(const QString& new_answer) override;
    void showWarningWhenNameEmpty() override;
    void connectSignals() override;

protected Q_SLOTS:
    bool validateFinishedOutput(int exit_code) override;
};




class TestDownloadCommandParser : public QObject
{
    Q_OBJECT

public:
    TestDownloadCommandParser(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockDownloadCommandParser download_command_parser;
};
