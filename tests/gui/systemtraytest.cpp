#include "systemtraytest.h"


MockSystemTray::MockSystemTray(MainWindow* parent) :
    SystemTray{parent}
{
  // ...
}


TestSystemTray::TestSystemTray(QObject* parent) :
    QObject{parent},
    system_tray{new MockMainWindow}
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestSystemTray::isSystemTrayStatusPassiveByDefault()
{
    QCOMPARE(system_tray.status(), KStatusNotifierItem::Passive);
}


void TestSystemTray::isSystemTrayStatusNeedsAttentionWhenPackagesCountIsGreaterThanZero()
{
    constexpr int packages_count = 5;
    system_tray.update(packages_count);

    QCOMPARE(system_tray.status(), KStatusNotifierItem::NeedsAttention);
}


void TestSystemTray::isSystemTrayStatusPassiveAfterWhenPackagesCountIsEqualToZeroAgain()
{
    int packages_count = 5;
    system_tray.update(packages_count);

    packages_count = 0;
    system_tray.update(packages_count);

    QCOMPARE(system_tray.status(), KStatusNotifierItem::Passive);
}


void TestSystemTray::cleanup()
{
    system_tray.changeStatusToDefault();
}
