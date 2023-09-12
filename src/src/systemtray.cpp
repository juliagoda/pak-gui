// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of CachyOS package manager based on "pak" application.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "systemtray.h"

#include "mainwindow.h"

#include <KLocalizedString>


SystemTray::SystemTray(MainWindow* parent)
    : KStatusNotifierItem{parent},
      main_window{parent}
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

    if (main_window->isMinimized() && packages_count > 0)
    {
        setStatus(KStatusNotifierItem::NeedsAttention);
        setToolTipTitle(i18n("Update"));
        setToolTipSubTitle(i18ncp("package to update", i18n("1 package to update").toStdString().c_str(), ("%1 " + i18n("packages to update")).toStdString().c_str(), packages_count));
    }
}


void SystemTray::changeStatusToDefault()
{
    setStatus(KStatusNotifierItem::Passive);
}
