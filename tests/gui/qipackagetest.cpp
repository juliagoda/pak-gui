#include "qipackagetest.h"


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
