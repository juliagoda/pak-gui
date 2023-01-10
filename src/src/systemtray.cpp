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
    setStatus(KStatusNotifierItem::Passive);
}


void SystemTray::update(int packages_count)
{
    setStatus(KStatusNotifierItem::Passive);
    if (packages_count > 0)
    {
        setStatus(KStatusNotifierItem::NeedsAttention);
        setToolTipTitle(i18n("Update"));
        setToolTipSubTitle(i18n("%1 packages to update", QString::number(packages_count)));
    }
}
