#include "gui/packagescolumnfixtures.h"
#include <QApplication>
#include <QtTest/QtTest>
#include <gtest/gtest.h>
#include <QWidget>

/*class MockMainWindowViewGtest : public MainWindowView
{
    Q_OBJECT

public:
    MOCK_METHOD(void, run, (), (override));

public Q_SLOTS:
    MOCK_METHOD(void, showStatisticsWindow, (), (override));
};*/


class MainWindowViewGuiTest : public ::testing::Test {
protected:
    void SetUp() override {
        main_window = new MockMainWindow();
        main_window_view = new MockMainWindowView(new QWidget);
        main_window->prepareProcess(QSharedPointer<MockProcess>(new MockProcess(main_window->actions_access_checker, main_window)));
        main_window->prepareMainWindowView(main_window_view);
        main_window->setCentralWidget(main_window_view);
        main_window->run();
    }

    void TearDown() override  {
        delete main_window_view;
        delete main_window;
    }

private:
    MockMainWindow* main_window;
    MockMainWindowView* main_window_view;

};

// Demonstrate some basic assertions.
TEST_F(MainWindowViewGuiTest, showPreviewForInstalledPackages) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}


// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
