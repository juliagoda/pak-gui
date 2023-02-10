 #include "logger.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockLogger : public Logger
{
    Q_OBJECT

public:
    explicit MockLogger();
    friend class TestLogger;
};



class TestLogger : public QObject
{
    Q_OBJECT

public:
    TestLogger(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockLogger logger;
};
