#include "actionsaccesscheckertest.h"



MockActionsAccessChecker::MockActionsAccessChecker(QWidget* new_parent) :
    ActionsAccessChecker(new_parent)
{
   const QString unknown_exec_file = "unknown";
   QStringList required_packages = QStringList() << unknown_exec_file;
   fillRequiredPackagesList(required_packages);
}


void MockActionsAccessChecker::showRequiredPackagesNotFoundWindow(const QStringList& not_installed_packages)
{
    Q_UNUSED(not_installed_packages)
}


bool MockActionsAccessChecker::checkNetworkInterfaces()
{
   return false;
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

