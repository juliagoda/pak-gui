#pragma once

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class TestSiPackage : public QObject
{
    Q_OBJECT

public:
    TestSiPackage(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    QString package_name = "";
    MockSiPackage si_package;
};
