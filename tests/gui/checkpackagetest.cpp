#include "checkpackagetest.h"


TestCheckPackage::TestCheckPackage(QObject* parent) :
    QObject(parent),
    check_package(package_content,
                  Package::Source::Unknown)
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestCheckPackage::cleanup()
{

}
