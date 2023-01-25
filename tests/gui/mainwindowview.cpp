#include "updatedpackagescolumn.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class TestMainWindowView : public QObject
{
    Q_OBJECT

public:
    TestMainWindowView(QObject* parent = nullptr);

private slots:
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


void TestMainWindowView::cleanup()
{

}

QTEST_MAIN(TestMainWindowView)
#include "mainwindowview.moc"
