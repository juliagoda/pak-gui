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
