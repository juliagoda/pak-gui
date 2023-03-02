#pragma once

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>



class TestPathConverter : public QObject
{
    Q_OBJECT

public:
    TestPathConverter(QObject* parent = nullptr);

private slots:
    void isRelativePathConvertedToAbsolutePath();
    void isAbsolutePathTheSameAfterConversion();
    void hasFullConfigPathCorrectForm();
};
