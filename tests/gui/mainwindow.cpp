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
    friend class TestInstalledPackagesColumn;
};

MockMainWindowView::MockMainWindowView() :
    MainWindowView(new QWidget)
{

}


class TestInstalledPackagesColumn : public QObject
{
    Q_OBJECT

public:
    TestInstalledPackagesColumn(QObject* parent = nullptr);

private slots:
    void showInstallationPreview();
    void hideInstallationPreview();
    void installationPreviewReadOnly();
    void searchCheckboxDisabledWithoutPackages();
    void searchCheckboxEnabledWithPackages();
    void searchInputOptionVisibleAfterButtonCheck();
    void reversedSortOptionVisibleAfterButtonCheck();
    void searchInputOptionHiddenAfterButtonUncheck();
    void reversedSortOptionHiddenAfterButtonUncheck();

    void cleanup();

private:
    MockMainWindowView main_window_view;
};


TestInstalledPackagesColumn::TestInstalledPackagesColumn(QObject* parent) :
    QObject(parent),
    main_window_view()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestInstalledPackagesColumn::showInstallationPreview()
{
    QTest::mouseClick(&*main_window_view.m_ui.console_view_uninstall, Qt::LeftButton);
    qDebug() << main_window_view.m_ui.console_view_uninstall->checkState();
    QVERIFY(!main_window_view.m_ui.installed_preview_area->isHidden());
}


void TestInstalledPackagesColumn::hideInstallationPreview()
{
    QTest::mouseClick(&*main_window_view.m_ui.console_view_uninstall, Qt::LeftButton);
    QTest::mouseClick(&*main_window_view.m_ui.console_view_uninstall, Qt::LeftButton);
    qDebug() << main_window_view.m_ui.console_view_uninstall->checkState();
    QVERIFY(main_window_view.m_ui.installed_preview_area->isHidden());
}


void TestInstalledPackagesColumn::installationPreviewReadOnly()
{
    QVERIFY(main_window_view.m_ui.text_browser_tab_uninstall->isReadOnly());
}


void TestInstalledPackagesColumn::searchCheckboxDisabledWithoutPackages()
{
    QVERIFY(!main_window_view.m_ui.search_installed_packages_checkbox->isEnabled());
}


void TestInstalledPackagesColumn::searchCheckboxEnabledWithPackages()
{
    main_window_view.m_ui.installed_packages_list->addItems(QStringList() << "gimp 2.10.32-3.1" << "qtcreator 9.0.1-1.1");
    QVERIFY(main_window_view.m_ui.search_installed_packages_checkbox->isEnabled());
}


void TestInstalledPackagesColumn::searchInputOptionVisibleAfterButtonCheck()
{
    main_window_view.m_ui.installed_packages_list->addItems(QStringList() << "gimp 2.10.32-3.1" << "qtcreator 9.0.1-1.1");
    QTest::mouseClick(&*main_window_view.m_ui.search_installed_packages_checkbox, Qt::LeftButton);
    QVERIFY(!main_window_view.m_ui.search_installed_packages_lineedit->isHidden());
}


void TestInstalledPackagesColumn::reversedSortOptionVisibleAfterButtonCheck()
{
    main_window_view.m_ui.installed_packages_list->addItems(QStringList() << "gimp 2.10.32-3.1" << "qtcreator 9.0.1-1.1");
    QTest::mouseClick(&*main_window_view.m_ui.search_installed_packages_checkbox, Qt::LeftButton);
    QVERIFY(!main_window_view.m_ui.sort_installed_packages->isHidden());
}


void TestInstalledPackagesColumn::searchInputOptionHiddenAfterButtonUncheck()
{
    main_window_view.m_ui.installed_packages_list->addItems(QStringList() << "gimp 2.10.32-3.1" << "qtcreator 9.0.1-1.1");
    QTest::mouseClick(&*main_window_view.m_ui.search_installed_packages_checkbox, Qt::LeftButton);
    QTest::mouseClick(&*main_window_view.m_ui.search_installed_packages_checkbox, Qt::LeftButton);
    QVERIFY(main_window_view.m_ui.search_installed_packages_lineedit->isHidden());
}


void TestInstalledPackagesColumn::reversedSortOptionHiddenAfterButtonUncheck()
{
    main_window_view.m_ui.installed_packages_list->addItems(QStringList() << "gimp 2.10.32-3.1" << "qtcreator 9.0.1-1.1");
    QTest::mouseClick(&*main_window_view.m_ui.search_installed_packages_checkbox, Qt::LeftButton);
    QTest::mouseClick(&*main_window_view.m_ui.search_installed_packages_checkbox, Qt::LeftButton);
    QVERIFY(main_window_view.m_ui.sort_installed_packages->isHidden());
}


void TestInstalledPackagesColumn::cleanup()
{
    main_window_view.m_ui.installed_packages_list->clear();
    main_window_view.m_ui.console_view_uninstall->setCheckState(Qt::Unchecked);
    main_window_view.m_ui.search_installed_packages_checkbox->setCheckState(Qt::Unchecked);
    main_window_view.m_ui.search_installed_packages_checkbox->setDisabled(true);
}

QTEST_MAIN(TestInstalledPackagesColumn)
#include "mainwindow.moc"
