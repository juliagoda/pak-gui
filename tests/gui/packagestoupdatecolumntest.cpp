// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of tests for CachyOS package manager (based on "pak" application).
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "packagestoupdatecolumntest.h"
#include "logger.h"
#include "qtestcase.h"

#include <KLocalizedString>


MockUpdatedPackagesColumn::MockUpdatedPackagesColumn(QListWidget* new_list_widget,
                                                     QLineEdit* new_search_lineedit,
                                                     QCheckBox* new_reverse_sort_checkbox,
                                                     QWidget* new_parent) :
    UpdatedPackagesColumn(new_list_widget, new_search_lineedit, new_reverse_sort_checkbox, new_parent)
{
   // ...
}


void MockUpdatedPackagesColumn::sort(bool is_sorted)
{
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


TestUpdatedPackagesColumn::TestUpdatedPackagesColumn(QObject* parent) :
    QObject(parent),
    main_window_view(new QWidget)
{
    main_window_view.init();
    QTestEventLoop::instance().enterLoop(1);
}


void TestUpdatedPackagesColumn::updatedColumnLabelHasProperContent()
{
    QCOMPARE(main_window_view.m_ui.packages_to_update_label->text(), i18n("TO UPDATE"));
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
   auto column = QSharedPointer<MockUpdatedPackagesColumn>(new MockUpdatedPackagesColumn(main_window_view.m_ui.packages_to_update_list, main_window_view.m_ui.search_packages_to_update_lineedit, main_window_view.m_ui.sort_packages_to_update, &main_window_view), &QObject::deleteLater);
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
   column->clearForSort();
}


void TestUpdatedPackagesColumn::checkedPackageIsStillCheckedAfterTextInputClear()
{
    auto column = QSharedPointer<MockUpdatedPackagesColumn>(new MockUpdatedPackagesColumn(main_window_view.m_ui.packages_to_update_list, main_window_view.m_ui.search_packages_to_update_lineedit, main_window_view.m_ui.sort_packages_to_update, &main_window_view), &QObject::deleteLater);
    column->fill();
    QTest::keyClicks(&*main_window_view.m_ui.search_packages_to_update_lineedit, "bin");
    auto items = main_window_view.m_ui.packages_to_update_list->findItems("*", Qt::MatchWildcard);
    qDebug() << "count after filter: " << main_window_view.m_ui.packages_to_update_list->findItems("*", Qt::MatchWildcard).count();

    if (items.empty())
        QSKIP("Don't check, if there are no items");

    items.first()->setCheckState(Qt::Checked);
    qDebug() << "checkstate: " << items.first()->checkState();
    QTest::keyClicks(&*main_window_view.m_ui.search_packages_to_update_lineedit, "");
    auto itemsAfterClear = main_window_view.m_ui.packages_to_update_list->findItems("bin", Qt::MatchStartsWith);
    QCOMPARE(itemsAfterClear.first()->checkState(), Qt::Checked);
    column->clearForSort();
}


void TestUpdatedPackagesColumn::textInputSortBya52IsEqualToOne()
{
    auto column = QSharedPointer<MockUpdatedPackagesColumn>(new MockUpdatedPackagesColumn(main_window_view.m_ui.packages_to_update_list, main_window_view.m_ui.search_packages_to_update_lineedit, main_window_view.m_ui.sort_packages_to_update, &main_window_view), &QObject::deleteLater);
    column->fill();
    QTest::keyClicks(&*main_window_view.m_ui.search_packages_to_update_lineedit, "bin");
    QCOMPARE(main_window_view.m_ui.packages_to_update_list->findItems("*", Qt::MatchWildcard).count(), 1);
    column->clearForSort();
}


void TestUpdatedPackagesColumn::textInputSortByaaIsEqualToZero()
{
    auto column = QSharedPointer<MockUpdatedPackagesColumn>(new MockUpdatedPackagesColumn(main_window_view.m_ui.packages_to_update_list, main_window_view.m_ui.search_packages_to_update_lineedit, main_window_view.m_ui.sort_packages_to_update, &main_window_view), &QObject::deleteLater);
    column->fill();
    QTest::keyClicks(&*main_window_view.m_ui.search_packages_to_update_lineedit, "aa");
    QCOMPARE(main_window_view.m_ui.packages_to_update_list->findItems("*", Qt::MatchWildcard).count(), 0);
    column->clearForSort();
}


void TestUpdatedPackagesColumn::allPackagesCheckedAfterButtonCheck()
{
    auto column = QSharedPointer<MockUpdatedPackagesColumn>(new MockUpdatedPackagesColumn(main_window_view.m_ui.packages_to_update_list, main_window_view.m_ui.search_packages_to_update_lineedit, main_window_view.m_ui.sort_packages_to_update, &main_window_view), &QObject::deleteLater);
    column->fill();
    QTest::mouseClick(&*main_window_view.m_ui.check_all_updates_checkbox, Qt::LeftButton);
    auto items = main_window_view.m_ui.packages_to_update_list->findItems("*", Qt::MatchWildcard);
    QVERIFY(std::all_of(std::begin(items), std::end(items), [](QListWidgetItem* item){ return item->checkState() == Qt::Checked; }));
    column->clearForSort();
}


void TestUpdatedPackagesColumn::allPackagesUncheckedAfterButtonUncheck()
{
    auto column = QSharedPointer<MockUpdatedPackagesColumn>(new MockUpdatedPackagesColumn(main_window_view.m_ui.packages_to_update_list, main_window_view.m_ui.search_packages_to_update_lineedit, main_window_view.m_ui.sort_packages_to_update, &main_window_view), &QObject::deleteLater);
    column->fill();
    QTest::mouseClick(&*main_window_view.m_ui.check_all_updates_checkbox, Qt::LeftButton);
    QTest::mouseClick(&*main_window_view.m_ui.check_all_updates_checkbox, Qt::LeftButton);
    auto items = main_window_view.m_ui.packages_to_update_list->findItems("*", Qt::MatchWildcard);
    QVERIFY(std::all_of(std::begin(items), std::end(items), [](QListWidgetItem* item){ return item->checkState() == Qt::Unchecked; }));
    column->clearForSort();
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
    auto column = QSharedPointer<MockUpdatedPackagesColumn>(new MockUpdatedPackagesColumn(main_window_view.m_ui.packages_to_update_list, main_window_view.m_ui.search_packages_to_update_lineedit, main_window_view.m_ui.sort_packages_to_update, &main_window_view), &QObject::deleteLater);
    column->fill();
    emit main_window_view.packagesToUpdateFillEnded();
    QVERIFY(!main_window_view.m_ui.packages_to_update_list->isHidden());
    column->clearForSort();
}


void TestUpdatedPackagesColumn::titleIsVisibleWhenPackagesListIsEmptyAfterSignalSend()
{
    emit main_window_view.packagesToUpdateFillEnded();
    QCOMPARE(main_window_view.m_ui.packages_to_update_label->text(), i18n("Cannot be updated - try to refresh"));
}


void TestUpdatedPackagesColumn::cleanup()
{
    disconnect(main_window_view.m_ui.sort_packages_to_update, &QCheckBox::toggled, main_window_view.updated_packages_column.data(), &UpdatedPackagesColumn::sort);
    main_window_view.m_ui.packages_to_update_list->clear();
    main_window_view.m_ui.search_packages_to_update_lineedit->clear();
    main_window_view.m_ui.console_view_update->setCheckState(Qt::Unchecked);
    main_window_view.m_ui.check_all_updates_checkbox->setCheckState(Qt::Unchecked);
    main_window_view.m_ui.search_packages_to_update_checkbox->setCheckState(Qt::Unchecked);
    main_window_view.m_ui.search_packages_to_update_checkbox->setDisabled(true);
    main_window_view.m_ui.update_packages_button->setEnabled(false);
    main_window_view.m_ui.sort_packages_to_update->setCheckState(Qt::Unchecked);

    while (main_window_view.m_ui.packages_to_update_list->count() > 0)
    {
        if (main_window_view.m_ui.packages_to_update_list->item(0))
            delete main_window_view.m_ui.packages_to_update_list->takeItem(0);
    }
}
