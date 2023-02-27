#include "actionsaccesscheckertest.h"



MockActionsAccessChecker::MockActionsAccessChecker(QWidget* new_parent) :
    ActionsAccessChecker(new_parent)
{
    QStringList unknown_packages = QStringList() << "example_of_required_package" << "pak";
    fillRequiredPackagesList(unknown_packages);
}


void MockActionsAccessChecker::showRequiredPackagesNotFoundWindow(const QStringList& not_installed_packages) const
{
    Q_UNUSED(not_installed_packages)
}


bool MockActionsAccessChecker::checkNetworkInterfaces() const
{
   return false;
}



TestActionsAccessChecker::TestActionsAccessChecker(QObject* parent) :
    QObject(parent),
    actions_access_checker(nullptr)
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestActionsAccessChecker::internetConnectionStateSignalEmittedAfterChange()
{
   QSignalSpy actions_access_checker_spy(&actions_access_checker, SIGNAL(internetAccessChanged(bool)));
   actions_access_checker.checkInternetConnection();

   QCOMPARE(actions_access_checker_spy.count(), 1);
   QVERIFY(!actions_access_checker_spy.takeFirst().at(0).toBool());
}


void TestActionsAccessChecker::stopApplicationSendSignalAfterNotFindingRequiredPackages()
{
   QSignalSpy actions_access_checker_spy(&actions_access_checker, SIGNAL(requiredPackagesNotFound()));
   actions_access_checker.findRequiredPackages();

   QCOMPARE(actions_access_checker_spy.count(), 1);
}


void TestActionsAccessChecker::initiallyPackagesAreNotFound()
{
   QVERIFY(!actions_access_checker.isAspInstalled());
   QVERIFY(!actions_access_checker.isAuracleInstalled());
   QVERIFY(!actions_access_checker.isGitInstalled());
   QVERIFY(!actions_access_checker.isReflectorInstalled());
}


void TestActionsAccessChecker::initiallyInternetConnectionIsOn()
{
    QVERIFY(actions_access_checker.isOnline());
}


void TestActionsAccessChecker::properlyFindsExecutableFileWithExampleOfPakQtests()
{
    QVERIFY(actions_access_checker.findPackage("pak-qtests"));
}


void TestActionsAccessChecker::emitSignalFunctionContainsEmitsForFourPackages()
{
   QSignalSpy asp_access_changed_spy(&actions_access_checker, SIGNAL(aspAccessChanged(bool)));
   QSignalSpy auracle_access_changed_spy(&actions_access_checker, SIGNAL(auracleAccessChanged(bool)));
   QSignalSpy reflector_access_changed_spy(&actions_access_checker, SIGNAL(reflectorAccessChanged(bool)));
   QSignalSpy git_access_changed_spy(&actions_access_checker, SIGNAL(gitAccessChanged(bool)));
   actions_access_checker.emitSignals();

   uint sum = asp_access_changed_spy.count() + auracle_access_changed_spy.count() +
              reflector_access_changed_spy.count() + git_access_changed_spy.count();

   QCOMPARE(sum, 4);
}


void TestActionsAccessChecker::cleanup()
{
   actions_access_checker.updateIsOnline(true);
}

