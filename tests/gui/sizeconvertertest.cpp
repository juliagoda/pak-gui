#include "sizeconvertertest.h"


TestSizeConverter::TestSizeConverter(QObject* parent) :
    QObject(parent),
    size_converter()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestSizeConverter::cleanup()
{
  // ...
}
