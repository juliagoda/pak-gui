#include "installedpackagescolumn.h"

#include "packagescolumnfixtures.h"
#include "qipackage.h"
#include "qnamespace.h"
#include "qtestcase.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockInstalledPackagesColumn : public InstalledPackagesColumn
{
    Q_OBJECT

public:
    explicit MockInstalledPackagesColumn(QListWidget* new_list_widget, QLineEdit* new_search_lineedit, QWidget* new_parent);
    friend class TestInstalledPackagesColumn;

protected:
    QStringList getPackagesList() override;

public Q_SLOTS:
    void sort(bool is_sorted) override;
};


MockInstalledPackagesColumn::MockInstalledPackagesColumn(QListWidget* new_list_widget, QLineEdit* new_search_lineedit, QWidget* new_parent) :
    InstalledPackagesColumn(new_list_widget, new_search_lineedit, new_parent)
{

}


void MockInstalledPackagesColumn::sort(bool is_sorted)
{
   Q_UNUSED(is_sorted)
   packages_sorter->sortReverse();
   list_widget->update();
}


QStringList MockInstalledPackagesColumn::getPackagesList()
{
    QString package_content1 = package_content_a52dec;
    QString package_content2 = package_content_alsa_utils;
    return QStringList() << package_content1 << package_content2;
}


class MockQiPackage : public QiPackage
{
public:
    explicit MockQiPackage(QString& package_content);
    friend class TestInstalledPackagesColumn;
};


MockQiPackage::MockQiPackage(QString& package_content) :
    QiPackage(package_content)
{

}


class TestInstalledPackagesColumn : public QObject
{
    Q_OBJECT

public:
    TestInstalledPackagesColumn(QObject* parent = nullptr);

private slots:
    void installationLabelHasProperContent();
    void showInstallationPreview();
    void hideInstallationPreview();
    void installatonPreviewHasDefaultStyle();
    void installationPreviewReadOnly();
    void searchCheckboxDisabledWithoutPackages();
    void searchCheckboxEnabledWithPackages();
    void searchInputOptionVisibleAfterButtonCheck();
    void reversedSortOptionVisibleAfterButtonCheck();
    void searchInputOptionHiddenAfterButtonUncheck();
    void reversedSortOptionHiddenAfterButtonUncheck();
    void uninstallButtonDisabledOnStart();
    void uninstallButtonEnabledAfterPackageCheck();
    void uninstallButtonDisabledAfterPackageUncheck();
    void uninstallButtonDisabledAfterPackagesRemove();
    void packagesOrderIsReversedAfterButtonCheck();
    void packageOrderIsAlphabeticallByDefault();
    void textInputSortBya52IsEqualToOne();
    void checkedPackageIsStillCheckedAfterTextInputClear();
    void textInputSortByaaIsEqualToZero();
    void animationsRunOnStart();
    void animationWidgetIsVisible();
    void packagesListIsHiddenOnStart();
    void animationIsHiddenAfterSignalSend();
    void notEmptyPackagesListIsVisibleAfterSignalSend();
    void titleIsVisibleWhenPackagesListIsEmptyAfterSignalSend();

    void cleanup();

private:
    MockMainWindowView main_window_view;
};


TestInstalledPackagesColumn::TestInstalledPackagesColumn(QObject* parent) :
    QObject(parent),
    main_window_view(new QWidget)
{
    main_window_view.init();
    QTestEventLoop::instance().enterLoop(1);
}


void TestInstalledPackagesColumn::installationLabelHasProperContent()
{
    QCOMPARE(main_window_view.m_ui.installed_packages_label->text(), QString("INSTALLED"));
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


void TestInstalledPackagesColumn::installatonPreviewHasDefaultStyle()
{
    QCOMPARE(main_window_view.m_ui.text_browser_tab_uninstall->styleSheet(), defaultStylesheet);
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
    main_window_view.m_ui.installed_packages_list->addItems(QStringList() << "a52dec-0.7.4-12.1" << "alsa-utils-1.2.8-1.1");
    QVERIFY(main_window_view.m_ui.search_installed_packages_checkbox->isEnabled());
}


void TestInstalledPackagesColumn::searchInputOptionVisibleAfterButtonCheck()
{
    main_window_view.m_ui.installed_packages_list->addItems(QStringList() << "a52dec-0.7.4-12.1" << "alsa-utils-1.2.8-1.1");
    QTest::mouseClick(&*main_window_view.m_ui.search_installed_packages_checkbox, Qt::LeftButton);
    QVERIFY(!main_window_view.m_ui.search_installed_packages_lineedit->isHidden());
}


void TestInstalledPackagesColumn::reversedSortOptionVisibleAfterButtonCheck()
{
    main_window_view.m_ui.installed_packages_list->addItems(QStringList() << "a52dec-0.7.4-12.1" << "alsa-utils-1.2.8-1.1");
    QTest::mouseClick(&*main_window_view.m_ui.search_installed_packages_checkbox, Qt::LeftButton);
    QVERIFY(!main_window_view.m_ui.sort_installed_packages->isHidden());
}


void TestInstalledPackagesColumn::searchInputOptionHiddenAfterButtonUncheck()
{
    main_window_view.m_ui.installed_packages_list->addItems(QStringList() << "a52dec-0.7.4-12.1" << "alsa-utils-1.2.8-1.1");
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


void TestInstalledPackagesColumn::uninstallButtonDisabledOnStart()
{
    QVERIFY(!main_window_view.m_ui.uninstall_packages_button->isEnabled());
}


void TestInstalledPackagesColumn::uninstallButtonEnabledAfterPackageCheck()
{
    QString package_content1 = package_content_a52dec;
    QScopedPointer<MockQiPackage> package1(new MockQiPackage(package_content1));
    main_window_view.m_ui.installed_packages_list->addItem(package1.get());
    package1->setCheckState(Qt::Checked);
    QVERIFY(main_window_view.m_ui.uninstall_packages_button->isEnabled());
}


void TestInstalledPackagesColumn::uninstallButtonDisabledAfterPackageUncheck()
{
    QString package_content1 = package_content_a52dec;
    QScopedPointer<MockQiPackage> package1(new MockQiPackage(package_content1));
    main_window_view.m_ui.installed_packages_list->addItem(package1.get());
    package1->setCheckState(Qt::Unchecked);
    QVERIFY(!main_window_view.m_ui.uninstall_packages_button->isEnabled());
}


void TestInstalledPackagesColumn::uninstallButtonDisabledAfterPackagesRemove()
{
    QString package_content1 = package_content_a52dec;
    QScopedPointer<MockQiPackage> package1(new MockQiPackage(package_content1));
    main_window_view.m_ui.installed_packages_list->addItem(package1.get());
    package1->setCheckState(Qt::Checked);
    main_window_view.m_ui.installed_packages_list->removeItemWidget(package1.get());
    package1.reset(nullptr);
    qDebug() << "Columns has " << main_window_view.m_ui.installed_packages_list->count() << "packages";
    QVERIFY(!main_window_view.m_ui.uninstall_packages_button->isEnabled());
}


void TestInstalledPackagesColumn::packagesOrderIsReversedAfterButtonCheck()
{
   auto column = QSharedPointer<MockInstalledPackagesColumn>(new MockInstalledPackagesColumn(main_window_view.m_ui.installed_packages_list, main_window_view.m_ui.search_installed_packages_lineedit, &main_window_view), &QObject::deleteLater);
   disconnect(main_window_view.m_ui.sort_installed_packages, &QCheckBox::toggled, main_window_view.installed_packages_column.data(), &InstalledPackagesColumn::sort);
   connect(main_window_view.m_ui.sort_installed_packages, &QCheckBox::toggled, column.data(), &MockInstalledPackagesColumn::sort);
   column->fill();
   QTest::mouseClick(&*main_window_view.m_ui.sort_installed_packages, Qt::LeftButton);
   qDebug() << "Sort button checkstate: " << main_window_view.m_ui.sort_installed_packages->checkState();
   auto first_package = dynamic_cast<QiPackage*>(main_window_view.m_ui.installed_packages_list->findItems("*", Qt::MatchWildcard).constFirst());
   auto last_package = dynamic_cast<QiPackage*>(main_window_view.m_ui.installed_packages_list->findItems("*", Qt::MatchWildcard).constLast());
   disconnect(main_window_view.m_ui.sort_installed_packages, &QCheckBox::toggled, column.data(), &MockInstalledPackagesColumn::sort);
   QCOMPARE(last_package->text(), "a52dec-0.7.4-12.1");
   QCOMPARE(first_package->text(), "alsa-utils-1.2.8-1.1");
}


void TestInstalledPackagesColumn::packageOrderIsAlphabeticallByDefault()
{
    auto column = QSharedPointer<MockInstalledPackagesColumn>(new MockInstalledPackagesColumn(main_window_view.m_ui.installed_packages_list, main_window_view.m_ui.search_installed_packages_lineedit, &main_window_view), &QObject::deleteLater);
    column->fill();
    auto first_package = dynamic_cast<QiPackage*>(main_window_view.m_ui.installed_packages_list->findItems("*", Qt::MatchWildcard).constFirst());
    auto last_package = dynamic_cast<QiPackage*>(main_window_view.m_ui.installed_packages_list->findItems("*", Qt::MatchWildcard).constLast());
    disconnect(main_window_view.m_ui.sort_installed_packages, &QCheckBox::toggled, column.data(), &MockInstalledPackagesColumn::sort);
    QCOMPARE(first_package->text(), "a52dec-0.7.4-12.1");
    QCOMPARE(last_package->text(), "alsa-utils-1.2.8-1.1");
}


void TestInstalledPackagesColumn::checkedPackageIsStillCheckedAfterTextInputClear()
{
    auto column = QSharedPointer<MockInstalledPackagesColumn>(new MockInstalledPackagesColumn(main_window_view.m_ui.installed_packages_list, main_window_view.m_ui.search_installed_packages_lineedit, &main_window_view), &QObject::deleteLater);
    column->fill();
    QTest::keyClicks(&*main_window_view.m_ui.search_installed_packages_lineedit, "a52");
    auto items = main_window_view.m_ui.installed_packages_list->findItems("*", Qt::MatchWildcard);
    qDebug() << "count after filter: " << main_window_view.m_ui.installed_packages_list->findItems("*", Qt::MatchWildcard).count();
    items.first()->setCheckState(Qt::Checked);
    qDebug() << "checkstate: " << items.first()->checkState();
    QTest::keyClicks(&*main_window_view.m_ui.search_installed_packages_lineedit, "");
    auto itemsAfterClear = main_window_view.m_ui.installed_packages_list->findItems("a52", Qt::MatchStartsWith);
    QCOMPARE(itemsAfterClear.first()->checkState(), Qt::Checked);
}


void TestInstalledPackagesColumn::textInputSortBya52IsEqualToOne()
{
    auto column = QSharedPointer<MockInstalledPackagesColumn>(new MockInstalledPackagesColumn(main_window_view.m_ui.installed_packages_list, main_window_view.m_ui.search_installed_packages_lineedit, &main_window_view), &QObject::deleteLater);
    column->fill();
    QTest::keyClicks(&*main_window_view.m_ui.search_installed_packages_lineedit, "a52");
    QCOMPARE(main_window_view.m_ui.installed_packages_list->findItems("*", Qt::MatchWildcard).count(), 1);
}



void TestInstalledPackagesColumn::textInputSortByaaIsEqualToZero()
{
    auto column = QSharedPointer<MockInstalledPackagesColumn>(new MockInstalledPackagesColumn(main_window_view.m_ui.installed_packages_list, main_window_view.m_ui.search_installed_packages_lineedit, &main_window_view), &QObject::deleteLater);
    column->fill();
    QTest::keyClicks(&*main_window_view.m_ui.search_installed_packages_lineedit, "aa");
    QCOMPARE(main_window_view.m_ui.installed_packages_list->findItems("*", Qt::MatchWildcard).count(), 0);
}


void TestInstalledPackagesColumn::animationsRunOnStart()
{
    QVERIFY(main_window_view.spinning_animation->isAnimationRunning());
}


void TestInstalledPackagesColumn::animationWidgetIsVisible()
{
    QVERIFY(!main_window_view.m_ui.remove_spinning_widget->isHidden());
}


void TestInstalledPackagesColumn::packagesListIsHiddenOnStart()
{
    QVERIFY(main_window_view.m_ui.installed_packages_list->isHidden());
}


void TestInstalledPackagesColumn::animationIsHiddenAfterSignalSend()
{
    emit main_window_view.installedPackagesFillEnded();
    QVERIFY(main_window_view.m_ui.remove_spinning_widget->isHidden());
}


void TestInstalledPackagesColumn::notEmptyPackagesListIsVisibleAfterSignalSend()
{
    auto column = QSharedPointer<MockInstalledPackagesColumn>(new MockInstalledPackagesColumn(main_window_view.m_ui.installed_packages_list, main_window_view.m_ui.search_installed_packages_lineedit, &main_window_view), &QObject::deleteLater);
    column->fill();
    emit main_window_view.installedPackagesFillEnded();
    QVERIFY(!main_window_view.m_ui.installed_packages_list->isHidden());
}


void TestInstalledPackagesColumn::titleIsVisibleWhenPackagesListIsEmptyAfterSignalSend()
{
    emit main_window_view.installedPackagesFillEnded();
    QCOMPARE(main_window_view.m_ui.installed_packages_label->text(), QString("Something went wrong. Try to refresh"));
}


void TestInstalledPackagesColumn::cleanup()
{
    connect(main_window_view.m_ui.sort_installed_packages, &QCheckBox::toggled, main_window_view.installed_packages_column.data(), &InstalledPackagesColumn::sort);
    main_window_view.m_ui.installed_packages_list->clear();
    main_window_view.m_ui.search_installed_packages_lineedit->clear();
    main_window_view.m_ui.console_view_uninstall->setCheckState(Qt::Unchecked);
    main_window_view.m_ui.search_installed_packages_checkbox->setCheckState(Qt::Unchecked);
    main_window_view.m_ui.search_installed_packages_checkbox->setDisabled(true);
    main_window_view.m_ui.uninstall_packages_button->setEnabled(false);
    main_window_view.m_ui.sort_installed_packages->setCheckState(Qt::Unchecked);

    while(main_window_view.m_ui.installed_packages_list->count() > 0)
    {
        if (main_window_view.m_ui.installed_packages_list->item(0))
            delete main_window_view.m_ui.installed_packages_list->takeItem(0);
    }
}

QTEST_MAIN(TestInstalledPackagesColumn)
#include "installedpackagescolumn.moc"
