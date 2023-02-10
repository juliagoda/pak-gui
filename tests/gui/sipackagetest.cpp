#include "sipackagetest.h"



MockSiPackage::MockSiPackage(QString& package_content) :
    SiPackage(package_content)
{
   // ...
}



TestSiPackage::TestSiPackage(QObject* parent) :
    QObject(parent),
    si_package(package_name)
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestSiPackage::cleanup()
{
  // ...
}
