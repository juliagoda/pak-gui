#include "qipackagetest.h"


MockQiPackage::MockQiPackage(QString& package_content) :
    QiPackage(package_content)
{
   // ...
}



TestQiPackage::TestQiPackage(QObject* parent) :
    QObject(parent),
    qi_package(package_name)
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestQiPackage::cleanup()
{
  // ...
}
