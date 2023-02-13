#pragma once

#include "process.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class TestProcess : public QObject
{
    Q_OBJECT

public:
    TestProcess(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockProcess process;
    QSharedPointer<ActionsAccessChecker> actions_checker = QSharedPointer<ActionsAccessChecker>(nullptr);
};

