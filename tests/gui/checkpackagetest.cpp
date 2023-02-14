#include "checkpackagetest.h"


TestCheckPackage::TestCheckPackage(QObject* parent) :
    QObject(parent),
    check_package(package_content,
                  Package::Source::Repo)
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestCheckPackage::cleanup()
{

}
