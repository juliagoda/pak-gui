#include "outputfiltertest.h"


TestOutputFilter::TestOutputFilter(QObject* parent) :
    QObject(parent),
    output_filter()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestOutputFilter::cleanup()
{

}
