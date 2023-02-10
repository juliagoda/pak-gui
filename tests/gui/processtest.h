#include "process.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockProcess : public Process
{
    Q_OBJECT

public:
    explicit MockProcess(QSharedPointer<ActionsAccessChecker>& new_actions_access_checker,
                         QWidget* new_parent);
    friend class TestProcess;
};




class TestProcess : public QObject
{
    Q_OBJECT

public:
    TestProcess(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockProcess process;
};

