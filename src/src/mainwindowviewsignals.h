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

#include "src/mainwindowview.h"

#include <QThread>


class MainWindowViewSignals : public QObject
{
    Q_OBJECT

public:
    explicit MainWindowViewSignals(MainWindowView* main_window_view);
   ~MainWindowViewSignals() override;

    void attachInputAnswerLines();
    void attachFillColumns();
    void startPackagesCheckTimer();
    virtual void startInternetCheckTimer();
    void initSignals();
    void initColumns();
    void attachCheckUpdates();

private:
    void attachConnectSignalsAfterFillEnd();
    void attachMainPreviewsVisibility();
    void attachPackagesAccess();
    void attachSignalsForSidePreviews();
    void attachSignalsForProcess();
    void attachAvailablePackagesColumn();
    void attachInstalledPackagesColumn();
    void attachPackagesToUpdateColumn();

    MainWindowView* main_window_view;
    QScopedPointer<QTimer> packages_timer{nullptr};
};

