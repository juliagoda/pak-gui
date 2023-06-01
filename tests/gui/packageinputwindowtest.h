#pragma once

#include "packageinputwindow.h"

#include <QtTest/QtTest>
#include <QWidget>


class MockPackageInputWindow : public PackageInputWindow
{
    Q_OBJECT

public:
    explicit MockPackageInputWindow(QWidget* parent = nullptr);
    friend class TestPackageInputWindow;
};


class TestPackageInputWindow : public QObject
{
    Q_OBJECT

public:
    TestPackageInputWindow(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockPackageInputWindow package_input_window;
};
