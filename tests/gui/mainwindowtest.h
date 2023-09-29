// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of tests for  package manager (based on "pak" application).
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

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class TestMainWindow : public QObject
{
    Q_OBJECT

public:
    TestMainWindow(QObject* parent = nullptr);

private slots:
    void ledLabelsContainCorrectTexts();
    void ledLabelsContainCorrectTooltips();
    void ledAreOffByDefault();
    void repositoriesLedIsOnWhenOnline();
    void aurLedIsOnWhenAuracleGitInstalledAndIsOnline();
    void polaurLedIsOnWhenGitInstalledAndIsOnline();
    void noInternetConnectionTextIsVisibleWhenInternetConnectionIsOff();
    void onlineActionsAreDisabledWhenInternetConnectionIsOff();
    void offlineActionsAreEnabledWhenInternetConnectionIsOff();
    void searchAndPreviewsWidgetsAreHiddenWhenInternetConnectionIsOff();
    void actionsAreDisabledAfterInitializationStart();
    void actionsAreEnabledAfterInitializationEnd();
    void updateMirrorsActionIsDisabledWhenReflectorPackageIsNotDetected();
    void updateMirrorsActionIsEnabledWhenReflectorPackageIsDetected();
    void viewProgressCheckboxIsHiddenByDefault();
    void viewProgressCheckboxIsVisibleDuringClean();
    void viewProgressCheckboxIsVisibleDuringMirrorsUpdate();
    void viewProgressCheckboxIsVisibleDuringVcsPackagesPrint();
    void viewProgressCheckboxIsVisibleDuringInstalledPackagesUpdate();
    void spinningAnimationForSideTaskIsVisibleDuringClean();
    void spinningAnimationForSideTaskIsVisibleDuringMirrorsUpdate();
    void spinningAnimationForSideTaskIsVisibleDuringVcsPackagesPrint();
    void spinningAnimationForSideTaskIsVisibleDuringInstalledPackagesUpdate();
    void viewProgressCheckboxIsHiddenAfterEndOfTasks();
    void spinningAnimationForSideTaskIsStoppedAfterEndOfTasks();

    void cleanup();

private:
    MockMainWindow main_window;
    MockMainWindowView main_window_view;
};
