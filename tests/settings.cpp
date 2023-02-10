#include "gui/packagescolumnfixtures.h"

#include "qnamespace.h"
#include "settings.h"

#include <QWidget>
#include <QApplication>
#include <QtTest/QtTest>
#include <gtest/gtest.h>
#include <gmock/gmock.h>


class MockMainWindowGtest : public MainWindow
{
    Q_OBJECT

public:
    MockMainWindowGtest() :
        MainWindow()
    {
        // ...
    }

    MOCK_METHOD(void, startSystemTray, (), (override));
    MOCK_METHOD(void, connectSignalForUpdateCheck, (), (override));
    MOCK_METHOD(void, connectSignalForHistoryStore, (), (override));

    friend class SettingsTest;
};


class MockMainWindowViewSettingsGtest : public MainWindowView
{
    Q_OBJECT

public:
    MockMainWindowViewSettingsGtest(QWidget* new_widget) :
        MainWindowView(new_widget)
    {
        // ...
    }

    MOCK_METHOD(void, updateWidgets, (), (override));

    friend class SettingsTest;
};


class MockSettings : public Settings
{
    Q_OBJECT

public:
    MockSettings(MainWindow* main_window) :
        Settings(main_window)
    {
        // ...
    }

     friend class SettingsTest;
};


class SettingsTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        main_window = new MockMainWindowGtest;
        main_window_view = new MockMainWindowViewSettingsGtest(main_window);
        main_window->prepareProcess(QSharedPointer<MockProcess>(new MockProcess(main_window->actions_access_checker,
                                                                                main_window)));
        main_window->prepareMainWindowView(main_window_view);
        main_window->setCentralWidget(main_window_view);
        main_window->run();

        settings = new MockSettings(main_window);
    }

    void TearDown() override
    {
        delete settings;
        delete main_window_view;
        delete main_window;
    }

    MockMainWindowGtest* main_window;
    MockMainWindowViewSettingsGtest* main_window_view;
    MockSettings* settings;
};


TEST_F(SettingsTest, initializedStartSystemTrayAfterSettingsUpdate)
{
    EXPECT_CALL(*main_window, startSystemTray());
    emit settings->settingsChanged("");
}

TEST_F(SettingsTest, initializedSignalForUpdateCheckConnectionAfterSettingsUpdate)
{
    EXPECT_CALL(*main_window, connectSignalForUpdateCheck());
    emit settings->settingsChanged("");
}

TEST_F(SettingsTest, initializedSignalForHistoryStoreConnectionAfterSettingsUpdate)
{
    EXPECT_CALL(*main_window, connectSignalForHistoryStore());
    emit settings->settingsChanged("");
}

TEST_F(SettingsTest, initializedWidgetsUpdateAfterSettingsUpdate)
{
    EXPECT_CALL(*main_window_view, updateWidgets());
    emit settings->settingsChanged("");
}


#include "settings.moc"
