#include "mainwindow.h"

#include "packagescolumnfixtures.h"
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

    void run() override;

    friend class TestMainWindow;
};


void MockMainWindow::run()
{
    qDebug() << "Run mock";
    prepareProcess(QSharedPointer<MockProcess>(new MockProcess(actions_access_checker, this)));
    prepareMainWindowView(new MockMainWindowView(this));
    setCentralWidget(main_window_view);
    startSystemTray();
    initSignals();
    setupGUI(Default, "pak-gui.rc");
    setXMLFile("pak-gui.rc");
}


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
    void viewProgressCheckboxIsHiddenByDefault();
    void viewProgressCheckboxIsVisibleDuringClean();
    void viewProgressCheckboxIsVisibleDuringMirrorsUpdate();
    void viewProgressCheckboxIsVisibleDuringVcsPackagesPrint();
    void viewProgressCheckboxIsVisibleDuringInstalledPackagesUpdate();
    void viewProgressCheckboxIsHiddenAfterEndOfTasks();

    void cleanup();

private:
    MockMainWindow main_window;
};


TestMainWindow::TestMainWindow(QObject* parent) :
    QObject(parent),
    main_window()
{
    main_window.run();
    QTestEventLoop::instance().enterLoop(1);
}


void TestMainWindow::ledLabelsContainCorrectTexts()
{

}


void TestMainWindow::ledLabelsContainCorrectTooltips()
{

}


void TestMainWindow::ledAreOffByDefault()
{

}


void TestMainWindow::repositoriesLedIsOnWhenOnline()
{

}


void TestMainWindow::aurLedIsOnWhenAuracleGitInstalledAndIsOnline()
{

}


void TestMainWindow::polaurLedIsOnWhenGitInstalledAndIsOnline()
{

}


void TestMainWindow::viewProgressCheckboxIsHiddenByDefault()
{

}


void TestMainWindow::viewProgressCheckboxIsVisibleDuringClean()
{

}


void TestMainWindow::viewProgressCheckboxIsVisibleDuringMirrorsUpdate()
{

}


void TestMainWindow::viewProgressCheckboxIsVisibleDuringVcsPackagesPrint()
{

}


void TestMainWindow::viewProgressCheckboxIsVisibleDuringInstalledPackagesUpdate()
{

}


void TestMainWindow::viewProgressCheckboxIsHiddenAfterEndOfTasks()
{

}


void TestMainWindow::cleanup()
{

}

QTEST_MAIN(TestMainWindow)
#include "mainwindow.moc"
