#include "mainwindow.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockMainWindow : public MainWindow
{
    Q_OBJECT

public:
    MockMainWindow() :
        MainWindow()
    {

    }

    friend class TestMainWindow;
};


class TestMainWindow : public QObject
{
    Q_OBJECT

public:
    TestMainWindow(QObject* parent = nullptr);

private slots:
    //  clean, mirrorsupdate, printvcspackages,update installed packages
    void ledLabelsContainCorrectTexts();
    void ledLabelsContainCorrectTooltips();
    void ledAreOffByDefault();
    void repositoriesLedIsOnWhenOnline();
    void aurLedIsOnWhenAuracleGitInstalledAndIsOnline();
    void polaurLedIsOnWhenGitInstalledAndIsOnline();
    void viewProgressCheckboxIsHiddenByDefault();
    void viewProgressCheckboxIsVisibleDuringClean();
    void viewProgressCheckboxIsVisibleDuringMirrorsUpdate();
    void viewProgressCheckboxIsVisibleDuringVcsPackagesPrint();
    void viewProgressCheckboxIsVisibleDuringInstalledPackagesUpdate();
    void viewProgressCheckboxIsHiddenAfterEndOfTasks();
    void

    void cleanup();

private:
    MockMainWindow main_window;
};


TestMainWindow::TestMainWindow(QObject* parent) :
    QObject(parent),
    main_window()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestMainWindow::cleanup()
{

}

QTEST_MAIN(TestMainWindow)
#include "mainwindow.moc"
