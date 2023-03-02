#pragma once

#include "systemtray.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockSystemTray : public SystemTray
{
    Q_OBJECT

public:
    explicit MockSystemTray(MainWindow* parent);
    friend class TestSystemTray;
};



class TestSystemTray : public QObject
{
    Q_OBJECT

public:
    TestSystemTray(QObject* parent = nullptr);

private slots:
    void isSystemTrayStatusPassiveByDefault();
    void isSystemTrayStatusNeedsAttentionWhenPackagesCountIsGreaterThanZero();
    void isSystemTrayStatusPassiveAfterWhenPackagesCountIsEqualToZeroAgain();
    void cleanup();

private:
    MockSystemTray system_tray;
};
