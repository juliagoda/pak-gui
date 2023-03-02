#pragma once

#include "packagescolumnfixtures.h"

#include "settings.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockSettings : public Settings
{
    Q_OBJECT

public:
    MockSettings(MainWindow* main_window) :
        Settings(main_window)
    {
        // ...
    }

     friend class TestSettingsWindow;
};


class TestSettingsWindow : public QObject
{
    Q_OBJECT

public:
    TestSettingsWindow(QObject* parent = nullptr);

private slots:
    void generalDefaultSettingsAreCorrectlyIntroduced();
    void previewsAppearanceDefaultSettingsAreCorrectlyIntroduced();
    void availablePackagesInfoDefaultSettingsAreCorrectlyIntroduced();
    void selectedPackagesInfoDefaultSettingsAreCorrectlyIntroduced();
    void logsDefaultSettingsAreCorrectlyIntroduced();
    void applyButtonIsEnabledAfterAnyGeneralSettingChange();
    void applyButtonIsEnabledAfterAnyPreviewsAppearanceSettingChange();
    void applyButtonIsEnabledAfterAnyPackagesOrderSettingChange();
    void applyButtonIsEnabledAfterAnyLogsSettingChange();
    //void initializedStartSystemTrayAfterSettingsUpdate();
    //void initializedSignalForUpdateCheckConnectionAfterSettingsUpdate();
    //void initializedSignalForHistoryStoreConnectionAfterSettingsUpdate();
    //void initializedWidgetsUpdateAfterSettingsUpdate();

    void cleanup();

private:
    MockMainWindow main_window;
    MockSettings settings;
};
