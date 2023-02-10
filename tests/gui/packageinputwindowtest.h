#include "packageinputwindowtest.h"



MockPackageInputWindow::MockPackageInputWindow(QWidget* new_parent) :
    PackageInputWindow(new_parent)
{

}



TestPackageInputWindow::TestPackageInputWindow(QObject* parent) :
    QObject(parent),
    package_input_window(new QWidget)
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestPackageInputWindow::cleanup()
{

}
