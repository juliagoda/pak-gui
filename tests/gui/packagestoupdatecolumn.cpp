#include "updatedpackagescolumn.h"

#include "packagescolumnfixtures.h"
#include "checkpackage.h"
#include "qnamespace.h"
#include "qtestcase.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockUpdatedPackagesColumn : public UpdatedPackagesColumn
{
    Q_OBJECT

public:
    explicit MockUpdatedPackagesColumn(QListWidget* new_list_widget,
                                       QLineEdit* new_search_lineedit,
                                       QWidget* new_parent);
    friend class TestUpdatedPackagesColumn;

protected:
    QHash<QString, Package::Source> getPackagesList() override;

public Q_SLOTS:
    void sort(bool is_sorted) override;
};


MockUpdatedPackagesColumn::MockUpdatedPackagesColumn(QListWidget* new_list_widget,
                                                     QLineEdit* new_search_lineedit,
                                                     QWidget* new_parent) :
    UpdatedPackagesColumn(new_list_widget, new_search_lineedit, new_parent)
{

}


void MockUpdatedPackagesColumn::sort(bool is_sorted)
{
    qDebug() << "sort in MockUpdatedPackagesColumn";
   Q_UNUSED(is_sorted)
   packages_sorter->sortReverse();
   list_widget->update();
}


QHash<QString, Package::Source> MockUpdatedPackagesColumn::getPackagesList()
{
    QHash<QString, Package::Source> packages_map;
    packages_map.insert(packages_to_update_content_binutils, Package::Source::Repo);
    packages_map.insert(packages_to_update_content_ddrescue, Package::Source::Repo);
    packages_map.insert(packages_to_update_content_fwupd, Package::Source::AUR);
    packages_map.insert(packages_to_update_content_konsole, Package::Source::POLAUR);
    return packages_map;
}


class MockCheckPackage : public CheckPackage
{
public:
    explicit MockCheckPackage(QString& package_content, Package::Source new_source);
    friend class TestUpdatedPackagesColumn;
};


MockCheckPackage::MockCheckPackage(QString& package_content, Package::Source new_source) :
    CheckPackage(package_content, new_source)
{

}


class TestUpdatedPackagesColumn : public QObject
{
    Q_OBJECT

public:
    TestUpdatedPackagesColumn(QObject* parent = nullptr);

private slots:
    void updatedColumnLabelHasProperContent();
    void showUpdatedColumnPreview();
    void hideUpdatedColumnPreview();
    void updatedColumnPreviewHasDefaultStyle();
    void updatedColumnPreviewReadOnly();
    void searchCheckboxDisabledWithoutPackages();
    void searchCheckboxEnabledWithPackages();
    void searchInputOptionVisibleAfterButtonCheck();
    void reversedSortOptionVisibleAfterButtonCheck();
    void searchInputOptionHiddenAfterButtonUncheck();
    void reversedSortOptionHiddenAfterButtonUncheck();
    void updateButtonDisabledOnStart();
    void updateButtonEnabledAfterPackageCheck();
    void updateButtonDisabledAfterPackageUncheck();
    void updateButtonDisabledAfterPackagesRemove();
    void packagesOrderIsReversedAfterButtonCheck();
    void checkedPackageIsStillCheckedAfterTextInputClear();
    void textInputSortBya52IsEqualToOne();
    void textInputSortByaaIsEqualToZero();
    void allPackagesCheckedAfterButtonCheck();
    void allPackagesUncheckedAfterButtonUncheck();
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


TestUpdatedPackagesColumn::TestUpdatedPackagesColumn(QObject* parent) :
    QObject(parent),
    main_window_view(new QWidget)
{
    main_window_view.init();
    QTestEventLoop::instance().enterLoop(1);
}


void TestUpdatedPackagesColumn::updatedColumnLabelHasProperContent()
{
    QCOMPARE(main_window_view.m_ui.packages_to_update_label->text(), QString("TO UPDATE"));
}


void TestUpdatedPackagesColumn::showUpdatedColumnPreview()
{
    QTest::mouseClick(&*main_window_view.m_ui.console_view_update, Qt::LeftButton);
    qDebug() << main_window_view.m_ui.console_view_update->checkState();
    QVERIFY(!main_window_view.m_ui.updated_preview_area->isHidden());
}


void TestUpdatedPackagesColumn::hideUpdatedColumnPreview()
{
    QTest::mouseClick(&*main_window_view.m_ui.console_view_update, Qt::LeftButton);
    QTest::mouseClick(&*main_window_view.m_ui.console_view_update, Qt::LeftButton);
    qDebug() << main_window_view.m_ui.console_view_update->checkState();
    QVERIFY(main_window_view.m_ui.updated_preview_area->isHidden());
}


void TestUpdatedPackagesColumn::updatedColumnPreviewHasDefaultStyle()
{
    QCOMPARE(main_window_view.m_ui.text_browser_tab_update->styleSheet(), defaultStylesheet);
}


void TestUpdatedPackagesColumn::updatedColumnPreviewReadOnly()
{
    QVERIFY(main_window_view.m_ui.text_browser_tab_update->isReadOnly());
}


void TestUpdatedPackagesColumn::searchCheckboxDisabledWithoutPackages()
{
    QVERIFY(!main_window_view.m_ui.search_packages_to_update_checkbox->isEnabled());
}


void TestUpdatedPackagesColumn::searchCheckboxEnabledWithPackages()
{
    main_window_view.m_ui.packages_to_update_list->addItems(QStringList() <<
                                                            "binutils-2.40-1.1 => 2.40-2.1" <<
                                                            "ddrescue 1.26-1.1 => 1.27-1.1 [REPO]");
    QVERIFY(main_window_view.m_ui.search_packages_to_update_checkbox->isEnabled());
}


void TestUpdatedPackagesColumn::searchInputOptionVisibleAfterButtonCheck()
{
    main_window_view.m_ui.packages_to_update_list->addItems(QStringList() <<
                                                            "binutils-2.40-1.1 => 2.40-2.1" <<
                                                            "ddrescue 1.26-1.1 => 1.27-1.1 [REPO]");
    QTest::mouseClick(&*main_window_view.m_ui.search_packages_to_update_checkbox, Qt::LeftButton);
    QVERIFY(!main_window_view.m_ui.search_packages_to_update_lineedit->isHidden());
}


void TestUpdatedPackagesColumn::reversedSortOptionVisibleAfterButtonCheck()
{
    main_window_view.m_ui.packages_to_update_list->addItems(QStringList() <<
                                                            "binutils-2.40-1.1 => 2.40-2.1" <<
                                                            "ddrescue 1.26-1.1 => 1.27-1.1 [REPO]");
    QTest::mouseClick(&*main_window_view.m_ui.search_packages_to_update_checkbox, Qt::LeftButton);
    QVERIFY(!main_window_view.m_ui.sort_packages_to_update->isHidden());
}


void TestUpdatedPackagesColumn::searchInputOptionHiddenAfterButtonUncheck()
{
    main_window_view.m_ui.packages_to_update_list->addItems(QStringList() <<
                                                            "binutils-2.40-1.1 => 2.40-2.1" <<
                                                            "ddrescue 1.26-1.1 => 1.27-1.1 [REPO]");
    QTest::mouseClick(&*main_window_view.m_ui.search_packages_to_update_checkbox, Qt::LeftButton);
    QTest::mouseClick(&*main_window_view.m_ui.search_packages_to_update_checkbox, Qt::LeftButton);
    QVERIFY(main_window_view.m_ui.search_packages_to_update_lineedit->isHidden());
}


void TestUpdatedPackagesColumn::reversedSortOptionHiddenAfterButtonUncheck()
{
    main_window_view.m_ui.packages_to_update_list->addItems(QStringList() <<
                                                            "binutils-2.40-1.1 => 2.40-2.1" <<
                                                            "ddrescue 1.26-1.1 => 1.27-1.1 [REPO]");
    QTest::mouseClick(&*main_window_view.m_ui.search_packages_to_update_checkbox, Qt::LeftButton);
    QTest::mouseClick(&*main_window_view.m_ui.search_packages_to_update_checkbox, Qt::LeftButton);
    QVERIFY(main_window_view.m_ui.sort_packages_to_update->isHidden());
}


void TestUpdatedPackagesColumn::updateButtonDisabledOnStart()
{
    QVERIFY(!main_window_view.m_ui.update_packages_button->isEnabled());
}


void TestUpdatedPackagesColumn::updateButtonEnabledAfterPackageCheck()
{
    QString package_content1 = packages_to_update_content_binutils;
    QScopedPointer<MockCheckPackage> package1(new MockCheckPackage(package_content1, Package::Source::Repo));
    main_window_view.m_ui.packages_to_update_list->addItem(package1.get());
    package1->setCheckState(Qt::Checked);
    QVERIFY(main_window_view.m_ui.update_packages_button->isEnabled());
}


void TestUpdatedPackagesColumn::updateButtonDisabledAfterPackageUncheck()
{
    QString package_content1 = packages_to_update_content_binutils;
    QScopedPointer<MockCheckPackage> package1(new MockCheckPackage(package_content1, Package::Source::Repo));
    main_window_view.m_ui.packages_to_update_list->addItem(package1.get());
    package1->setCheckState(Qt::Unchecked);
    QVERIFY(!main_window_view.m_ui.update_packages_button->isEnabled());
}


void TestUpdatedPackagesColumn::updateButtonDisabledAfterPackagesRemove()
{
    QString package_content1 = packages_to_update_content_binutils;
    QScopedPointer<MockCheckPackage> package1(new MockCheckPackage(package_content1, Package::Source::Repo));
    main_window_view.m_ui.packages_to_update_list->addItem(package1.get());
    package1->setCheckState(Qt::Checked);
    main_window_view.m_ui.packages_to_update_list->removeItemWidget(package1.get());
    package1.reset(nullptr);
    qDebug() << "Columns has " << main_window_view.m_ui.packages_to_update_list->count() << "packages";
    QVERIFY(!main_window_view.m_ui.update_packages_button->isEnabled());
}


void TestUpdatedPackagesColumn::packagesOrderIsReversedAfterButtonCheck()
{
   auto column = QSharedPointer<MockUpdatedPackagesColumn>(new MockUpdatedPackagesColumn(main_window_view.m_ui.packages_to_update_list, main_window_view.m_ui.search_packages_to_update_lineedit, &main_window_view), &QObject::deleteLater);
   disconnect(main_window_view.m_ui.sort_packages_to_update, &QCheckBox::toggled, main_window_view.updated_packages_column.data(), &UpdatedPackagesColumn::sort);
   connect(main_window_view.m_ui.sort_packages_to_update, &QCheckBox::toggled, column.data(), &MockUpdatedPackagesColumn::sort);
   column->fill();
   auto first_package_before_sort = dynamic_cast<CheckPackage*>(main_window_view.m_ui.packages_to_update_list->findItems("*", Qt::MatchWildcard).constFirst());
   auto last_package_before_sort = dynamic_cast<CheckPackage*>(main_window_view.m_ui.packages_to_update_list->findItems("*", Qt::MatchWildcard).constLast());
   QTest::mouseClick(&*main_window_view.m_ui.sort_packages_to_update, Qt::LeftButton);
   qDebug() << "Sort button checkstate: " << main_window_view.m_ui.sort_packages_to_update->checkState();
   auto first_package = dynamic_cast<CheckPackage*>(main_window_view.m_ui.packages_to_update_list->findItems("*", Qt::MatchWildcard).constFirst());
   auto last_package = dynamic_cast<CheckPackage*>(main_window_view.m_ui.packages_to_update_list->findItems("*", Qt::MatchWildcard).constLast());
   disconnect(main_window_view.m_ui.sort_packages_to_update, &QCheckBox::toggled, column.data(), &MockUpdatedPackagesColumn::sort);
   QCOMPARE(first_package->text(), last_package_before_sort->text());
   QCOMPARE(last_package->text(), first_package_before_sort->text());
}


void TestUpdatedPackagesColumn::checkedPackageIsStillCheckedAfterTextInputClear()
{
    auto column = QSharedPointer<MockUpdatedPackagesColumn>(new MockUpdatedPackagesColumn(main_window_view.m_ui.packages_to_update_list, main_window_view.m_ui.search_packages_to_update_lineedit, &main_window_view), &QObject::deleteLater);
    column->fill();
    QTest::keyClicks(&*main_window_view.m_ui.search_packages_to_update_lineedit, "bin");
    auto items = main_window_view.m_ui.packages_to_update_list->findItems("*", Qt::MatchWildcard);
    qDebug() << "count after filter: " << main_window_view.m_ui.packages_to_update_list->findItems("*", Qt::MatchWildcard).count();
    items.first()->setCheckState(Qt::Checked);
    qDebug() << "checkstate: " << items.first()->checkState();
    QTest::keyClicks(&*main_window_view.m_ui.search_packages_to_update_lineedit, "");
    auto itemsAfterClear = main_window_view.m_ui.packages_to_update_list->findItems("bin", Qt::MatchStartsWith);
    QCOMPARE(itemsAfterClear.first()->checkState(), Qt::Checked);
}


void TestUpdatedPackagesColumn::textInputSortBya52IsEqualToOne()
{
    auto column = QSharedPointer<MockUpdatedPackagesColumn>(new MockUpdatedPackagesColumn(main_window_view.m_ui.packages_to_update_list, main_window_view.m_ui.search_packages_to_update_lineedit, &main_window_view), &QObject::deleteLater);
    column->fill();
    QTest::keyClicks(&*main_window_view.m_ui.search_packages_to_update_lineedit, "bin");
    QCOMPARE(main_window_view.m_ui.packages_to_update_list->findItems("*", Qt::MatchWildcard).count(), 1);
}


void TestUpdatedPackagesColumn::textInputSortByaaIsEqualToZero()
{
    auto column = QSharedPointer<MockUpdatedPackagesColumn>(new MockUpdatedPackagesColumn(main_window_view.m_ui.packages_to_update_list, main_window_view.m_ui.search_packages_to_update_lineedit, &main_window_view), &QObject::deleteLater);
    column->fill();
    QTest::keyClicks(&*main_window_view.m_ui.search_packages_to_update_lineedit, "aa");
    QCOMPARE(main_window_view.m_ui.packages_to_update_list->findItems("*", Qt::MatchWildcard).count(), 0);
}


void TestUpdatedPackagesColumn::allPackagesCheckedAfterButtonCheck()
{
    auto column = QSharedPointer<MockUpdatedPackagesColumn>(new MockUpdatedPackagesColumn(main_window_view.m_ui.packages_to_update_list, main_window_view.m_ui.search_packages_to_update_lineedit, &main_window_view), &QObject::deleteLater);
    column->fill();
    QTest::mouseClick(&*main_window_view.m_ui.check_all_updates_checkbox, Qt::LeftButton);
    auto items = main_window_view.m_ui.packages_to_update_list->findItems("*", Qt::MatchWildcard);
    QVERIFY(std::all_of(std::begin(items), std::end(items), [](QListWidgetItem* item){ return item->checkState() == Qt::Checked; }));
}


void TestUpdatedPackagesColumn::allPackagesUncheckedAfterButtonUncheck()
{
    auto column = QSharedPointer<MockUpdatedPackagesColumn>(new MockUpdatedPackagesColumn(main_window_view.m_ui.packages_to_update_list, main_window_view.m_ui.search_packages_to_update_lineedit, &main_window_view), &QObject::deleteLater);
    column->fill();
    QTest::mouseClick(&*main_window_view.m_ui.check_all_updates_checkbox, Qt::LeftButton);
    QTest::mouseClick(&*main_window_view.m_ui.check_all_updates_checkbox, Qt::LeftButton);
    auto items = main_window_view.m_ui.packages_to_update_list->findItems("*", Qt::MatchWildcard);
    QVERIFY(std::all_of(std::begin(items), std::end(items), [](QListWidgetItem* item){ return item->checkState() == Qt::Unchecked; }));
}


void TestUpdatedPackagesColumn::animationsRunOnStart()
{
    QVERIFY(main_window_view.spinning_animation->isAnimationRunning());
}


void TestUpdatedPackagesColumn::animationWidgetIsVisible()
{
    QVERIFY(!main_window_view.m_ui.update_spinning_widget->isHidden());
}


void TestUpdatedPackagesColumn::packagesListIsHiddenOnStart()
{
    QVERIFY(main_window_view.m_ui.packages_to_update_list->isHidden());
}


void TestUpdatedPackagesColumn::animationIsHiddenAfterSignalSend()
{
    emit main_window_view.packagesToUpdateFillEnded();
    QVERIFY(main_window_view.m_ui.update_spinning_widget->isHidden());
}


void TestUpdatedPackagesColumn::notEmptyPackagesListIsVisibleAfterSignalSend()
{
    auto column = QSharedPointer<MockUpdatedPackagesColumn>(new MockUpdatedPackagesColumn(main_window_view.m_ui.packages_to_update_list, main_window_view.m_ui.search_packages_to_update_lineedit, &main_window_view), &QObject::deleteLater);
    column->fill();
    emit main_window_view.packagesToUpdateFillEnded();
    QVERIFY(!main_window_view.m_ui.packages_to_update_list->isHidden());
}


void TestUpdatedPackagesColumn::titleIsVisibleWhenPackagesListIsEmptyAfterSignalSend()
{
    emit main_window_view.packagesToUpdateFillEnded();
    QCOMPARE(main_window_view.m_ui.packages_to_update_label->text(), QString("Cannot be updated - try to refresh"));
}


void TestUpdatedPackagesColumn::cleanup()
{
    connect(main_window_view.m_ui.sort_packages_to_update, &QCheckBox::toggled, main_window_view.updated_packages_column.data(), &UpdatedPackagesColumn::sort);
    main_window_view.m_ui.packages_to_update_list->clear();
    main_window_view.m_ui.search_packages_to_update_lineedit->clear();
    main_window_view.m_ui.console_view_update->setCheckState(Qt::Unchecked);
    main_window_view.m_ui.check_all_updates_checkbox->setCheckState(Qt::Unchecked);
    main_window_view.m_ui.search_packages_to_update_checkbox->setCheckState(Qt::Unchecked);
    main_window_view.m_ui.search_packages_to_update_checkbox->setDisabled(true);
    main_window_view.m_ui.update_packages_button->setEnabled(false);
    main_window_view.m_ui.sort_packages_to_update->setCheckState(Qt::Unchecked);

    while(main_window_view.m_ui.packages_to_update_list->count() > 0)
    {
        if (main_window_view.m_ui.packages_to_update_list->item(0))
            delete main_window_view.m_ui.packages_to_update_list->takeItem(0);
    }
}

QTEST_MAIN(TestUpdatedPackagesColumn)
#include "packagestoupdatecolumn.moc"
