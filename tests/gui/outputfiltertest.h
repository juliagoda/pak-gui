#pragma once

#include "outputfilter.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class TestOutputFilter : public QObject
{
    Q_OBJECT

public:
    TestOutputFilter(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    OutputFilter output_filter;
};
