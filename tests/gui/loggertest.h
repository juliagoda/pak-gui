#pragma once

#include "logger.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class  MockLogger : public Logger
{
    Q_OBJECT

public:
    explicit MockLogger() = default;
    friend class TestLogger;
};



class TestLogger : public QObject
{
    Q_OBJECT

public:
    TestLogger(QObject* parent = nullptr);

private slots:
    void writeSectionToFileMethodHasCorrectTextFormat();
    void writeLineToFileMethodHasCorrectTextFormat();
    void writeToFileMethodHasCorrectTextFormat();
    void logIntoFileMethodHasCorrectTextFormat();
    void cleanup();

private:
    MockLogger logger;
    QString text{"text"};
    const Logger::WriteOperations write_operation{Logger::WriteOperations::Install};

};
