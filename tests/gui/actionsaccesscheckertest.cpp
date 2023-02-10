#include "actionsaccesscheckertest.h"



MockActionsAccessChecker::MockActionsAccessChecker(QWidget* new_parent) :
    ActionsAccessChecker(new_parent)
{

}



TestActionsAccessChecker::TestActionsAccessChecker(QObject* parent) :
    QObject(parent),
    actions_access_checker(new QWidget)
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestActionsAccessChecker::cleanup()
{

}

