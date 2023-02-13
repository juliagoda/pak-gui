#pragma once

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class TestQiPackage : public QObject
{
    Q_OBJECT

public:
    TestQiPackage(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    QString package_name = "";
    MockQiPackage qi_package;
};
