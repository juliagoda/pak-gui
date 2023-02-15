#include <gtest/gtest.h>
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}

