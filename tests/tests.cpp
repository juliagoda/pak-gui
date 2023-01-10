#include <gtest/gtest.h>
#include <QtTest/QtTest>

/*class MainWindowViewGuiTest : public ::testing::Test {
protected:
    //QSharedPointer<PreviewDesign> main_window_view = nullptr;
    void SetUp() override {
   //   main_window_view.reset(new PreviewDesign);
    }

    void TearDown() override  {
    //  main_window_view.clear();
    }

};

// Demonstrate some basic assertions.
TEST_F(MainWindowViewGuiTest, showPreviewForInstalledPackages) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
*/

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
