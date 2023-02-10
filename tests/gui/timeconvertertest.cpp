#include "timeconvertertest.h"



TestTimeConverter::TestTimeConverter(QObject* parent) :
    QObject(parent),
    time_converter()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestTimeConverter::cleanup()
{
  // ...
}
