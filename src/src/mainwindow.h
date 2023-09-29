// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of  package manager based on "pak" application.
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

#pragma once

#include <KXmlGuiWindow>
#include <QSharedPointer>
#include <QScopedPointer>
#include <QPointer>
#include <QTimer>
#include <QKeySequence>
#include <QCloseEvent>

#include "process.h"
#include "actionsaccesschecker.h"
#include "systemtray.h"
#include "settings.h"


class MainWindowView;

class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() override;

    virtual void run();
    void detachSettingsSignal();

public Q_SLOTS:
    virtual void startSystemTray();
    void setTimersOnChecks();

private Q_SLOTS:
    void settingsConfigure();
    void enableActions();
    void disableActions();
    void disableOnlineActions();

signals:
    void closeApp();
    void widgetsChanged();
    void updatedPackageInfoList();

protected:
    void prepareMainWindowView(MainWindowView* new_main_window_view);
    void prepareProcess(const QWeakPointer<Process>& new_process);
    void initSignals();
    void closeEvent(QCloseEvent* event) override;
    virtual void connectSignalForUpdateCheck();
    virtual void connectSignalForHistoryStore();

    QPointer<MainWindowView> main_window_view;
    QSharedPointer<ActionsAccessChecker> actions_access_checker;
    QSharedPointer<Process> process;
    QPointer<Settings> settings_window;
    QTimer timer_on_updates;
    QTimer timer_on_logs;
    QPointer<QAction> update_action;
    QPointer<QAction> refresh_action;
    QPointer<QAction> download_action;
    QPointer<QAction> search_action;
    QPointer<QAction> print_statistics_action;
    QPointer<QAction> update_all_action;
    QPointer<QAction> update_mirrors_action;
    QPointer<QAction> clean_action;
    QPointer<QAction> sync_polaur_action;
    QScopedPointer<SystemTray> system_tray_icon{nullptr};

private:
    void startTimerOnOperation(const QDateTime& time,
                               QTimer& timer,
                               int time_limit_in_milliseconds,
                               const QString& operation);
    void setAction(QPointer<QAction>& action,
                   const QString& text,
                   const QString& icon,
                   const QKeySequence& key_sequence);

    bool initEnded{false};

};
