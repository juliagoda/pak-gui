#pragma once

#include "timeconverter.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>



class TestTimeConverter : public QObject
{
    Q_OBJECT

public:
    TestTimeConverter(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    TimeConverter time_converter;
};
