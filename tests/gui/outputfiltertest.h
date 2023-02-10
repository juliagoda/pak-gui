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


TestOutputFilter::TestOutputFilter(QObject* parent) :
    QObject(parent),
    output_filter()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestOutputFilter::cleanup()
{

}
