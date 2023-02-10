 #include "loggertest.h"


MockLogger::MockLogger() :
    Logger()
{
  // ...
}


MockActionsAccessChecker::MockActionsAccessChecker(QWidget* new_parent) :
    ActionsAccessChecker(new_parent)
{

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
