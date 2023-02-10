 #include "checkpackagetest.h"


MockCheckPackage::MockCheckPackage(const QString& package_content,
                                   Package::Source new_source) :
    CheckPackage(package_content, new_source)
{

}



TestCheckPackage::TestCheckPackage(QObject* parent) :
    QObject(parent),
    check_package(QString(""),
                  Package::Source::Unknown)
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestCheckPackage::cleanup()
{

}
