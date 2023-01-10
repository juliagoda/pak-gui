#include "mainwindowview.h"
#include "qnamespace.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>

class MockMainWindowView : public MainWindowView
{
    Q_OBJECT

public:
    MockMainWindowView();
    friend class TestMainWindowView;
};

MockMainWindowView::MockMainWindowView() :
    MainWindowView(new QWidget)
{

}


class TestMainWindowView : public QObject
{
    Q_OBJECT

public:
    TestMainWindowView(QObject* parent = nullptr);

private slots:
    void showInstallationPreview();
    void hideInstallationPreview();
    void cleanup();

private:
    MockMainWindowView main_window_view;
};

TestMainWindowView::TestMainWindowView(QObject* parent) :
    QObject(parent),
    main_window_view()
{
    QTestEventLoop::instance().enterLoop(1);
}

void TestMainWindowView::showInstallationPreview()
{
    QTest::mouseClick(&*main_window_view.m_ui.console_view_uninstall, Qt::LeftButton);
    qDebug() << main_window_view.m_ui.console_view_uninstall->checkState();
    QVERIFY(!main_window_view.m_ui.installed_preview_area->isHidden());
}

void TestMainWindowView::hideInstallationPreview()
{
    QTest::mouseClick(&*main_window_view.m_ui.console_view_uninstall, Qt::LeftButton);
    qDebug() << main_window_view.m_ui.console_view_uninstall->checkState();
    QVERIFY(main_window_view.m_ui.installed_preview_area->isHidden());
}

void TestMainWindowView::cleanup()
{
    qDebug() << "should be reset in there";
}

QTEST_MAIN(TestMainWindowView)
#include "mainwindow.moc"
