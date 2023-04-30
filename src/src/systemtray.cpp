#include "systemtray.h"

#include "mainwindow.h"

#include <KLocalizedString>


SystemTray::SystemTray(MainWindow* parent)
    : KStatusNotifierItem{parent}
{
    setup(parent);
}


void SystemTray::setup(QWidget* parent)
{
    setStandardActionsEnabled(true);
    setAssociatedWidget(parent);
    setIconByName(QStringLiteral("pak-gui"));
    changeStatusToDefault();
}


void SystemTray::update(uint packages_count)
{
    changeStatusToDefault();

    if (packages_count > 0)
    {
        setStatus(KStatusNotifierItem::NeedsAttention);
        setToolTipTitle(i18n("Update"));
        setToolTipSubTitle(i18np("1 package to update", "%2 packages to update", packages_count, QString::number(packages_count)));
    }
}


void SystemTray::changeStatusToDefault()
{
    setStatus(KStatusNotifierItem::Passive);
}
