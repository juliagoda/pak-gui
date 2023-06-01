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
    void isItemCheckable();
    void isItemNotCheckedByDefault();
    void isItemNameEqualToBinutils();
    void isItemVersionCorrectlyVisible();
    void isSourceEqualToRepo();

private:
    MockCheckPackage check_package;
};
