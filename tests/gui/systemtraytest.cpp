#include "systemtraytest.h"


MockSystemTray::MockSystemTray(MainWindow* parent) :
    SystemTray(parent)
{
  // ...
}



TestSystemTray::TestSystemTray(QObject* parent) :
    QObject(parent),
    system_tray(new MainWindow)
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestSystemTray::cleanup()
{
  // ...
}