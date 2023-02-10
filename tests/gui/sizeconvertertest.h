#include "sizeconverter.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>



class TestSizeConverter : public QObject
{
    Q_OBJECT

public:
    TestSizeConverter(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    SizeConverter size_converter;
};
