#include "gui/packagescolumnfixtures.h"

#include <QWidget>
#include <QApplication>
#include <QtTest/QtTest>
#include <gtest/gtest.h>
#include <gmock/gmock.h>


class MockMainWindowViewGtest : public MainWindowView
{
    Q_OBJECT

public:
    MockMainWindowViewGtest(QWidget* new_widget) :
        MainWindowView(new_widget)
    {
        // ...
    }

    //MOCK_METHOD(void, run, (), (override));
    MOCK_METHOD(void, showStatisticsWindow, (), (override));
    MOCK_METHOD(void, downloadPackage, (), (override));
    MOCK_METHOD(void, searchPackage, (), (override));
    //MOCK_METHOD(void, checkUpdates, (), (override));
    MOCK_METHOD(void, showFinishInformation, (), (override));
};


class MainWindowViewGuiTest : public ::testing::Test
{
protected:
    void SetUp() override {
        main_window = new MockMainWindow;
        main_window_view = new MockMainWindowViewGtest(main_window);
        main_window->prepareProcess(QSharedPointer<MockProcess>(new MockProcess(main_window->actions_access_checker,
                                                                                main_window)));
        main_window->prepareMainWindowView(main_window_view);
        main_window->setCentralWidget(main_window_view);
        main_window->run();
    }

    void TearDown() override  {
        delete main_window_view;
        delete main_window;
    }

    MockMainWindow* main_window;
    MockMainWindowViewGtest* main_window_view;
};

TEST_F(MainWindowViewGuiTest, triggeredSearchPackageAction)
{
    EXPECT_CALL(*main_window_view, searchPackage());
    main_window->triggerSearchPackageAction();
}

TEST_F(MainWindowViewGuiTest, triggeredShowStatisticsAction)
{
    EXPECT_CALL(*main_window_view, showStatisticsWindow());
    main_window->triggerShowStatisticsWindow();
}

TEST_F(MainWindowViewGuiTest, triggeredDownloadPackageAction)
{
    EXPECT_CALL(*main_window_view, downloadPackage());
    main_window->triggerDownloadPackageAction();
}


#include "tests.moc"
