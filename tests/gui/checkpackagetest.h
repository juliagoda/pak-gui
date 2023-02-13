#pragma once

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>



class TestCheckPackage : public QObject
{
    Q_OBJECT

public:
    TestCheckPackage(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockCheckPackage check_package;
    QString package_content = "";
};
