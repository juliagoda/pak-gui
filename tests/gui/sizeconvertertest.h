#pragma once

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class TestSizeConverter : public QObject
{
    Q_OBJECT

public:
    TestSizeConverter(QObject* parent = nullptr);

private slots:
    void is2000000BytesEqualTo2Megabytes();
    void is2MegabytesEqualTo2000000Bytes();
};
