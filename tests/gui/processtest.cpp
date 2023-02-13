#include "processtest.h"


TestProcess::TestProcess(QObject* parent) :
    QObject(parent),
    process(actions_checker, new QWidget)
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestProcess::cleanup()
{
  // ...
}
