#include "pathconverter.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>



class TestPathConverter : public QObject
{
    Q_OBJECT

public:
    TestPathConverter(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    PathConverter path_converter;
};
