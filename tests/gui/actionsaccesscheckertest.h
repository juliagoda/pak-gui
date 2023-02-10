#pragma once

#include "actionsaccesschecker.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockActionsAccessChecker : public ActionsAccessChecker
{
    Q_OBJECT

public:
    explicit MockActionsAccessChecker(QWidget* new_parent);
    friend class TestActionsAccessChecker;
};




class TestActionsAccessChecker : public QObject
{
    Q_OBJECT

public:
    TestActionsAccessChecker(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockActionsAccessChecker actions_access_checker;
};


