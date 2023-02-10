#include "processtest.h"



MockProcess::MockProcess(QSharedPointer<ActionsAccessChecker>& new_actions_access_checker,
                         QWidget* new_parent) :
    Process(new_actions_access_checker, new_parent)
{
  // ...
}



TestProcess::TestProcess(QObject* parent) :
    QObject(parent),
    process(new QWidget)
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestProcess::cleanup()
{
  // ...
}
