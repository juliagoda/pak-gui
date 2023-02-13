#pragma once

#include "defs.h"

#include <QtTest/QtTest>
#include <QWidget>


class TestDefs : public QObject
{
    Q_OBJECT

public:
    TestDefs(QObject* parent = nullptr);

private slots:
    void packageQiNameLineIsEqualToZero();
    void cleanup();
};
