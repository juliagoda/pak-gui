#include "loggertest.h"


MockLogger::MockLogger() :
    Logger()
{
  // ...
}



TestLogger::TestLogger(QObject* parent) :
    QObject(parent),
    logger()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestLogger::cleanup()
{
  // ...
}
