#include "availablepackagescolumntest.h"




MockAvailablePackagesColumn::MockAvailablePackagesColumn(QListWidget* new_list_widget,
                                                         QLineEdit* new_search_lineedit,
                                                         QWidget* new_parent) :
    AvailablePackagesColumn(new_list_widget, new_search_lineedit, new_parent)
{

}


void MockAvailablePackagesColumn::sort(bool is_sorted)
{
   Q_UNUSED(is_sorted)
   packages_sorter->sortReverse();
   list_widget->update();
}


QStringList MockAvailablePackagesColumn::getPackagesList()
{
    QString package_content1 = package_content_a52dec_si;
    QString package_content2 = package_content_alsa_utils_si;
    return QStringList() << package_content1 << package_content2;
}




MockSiPackage::MockSiPackage(QString& package_content) :
    SiPackage(package_content)
{

}




TestAvailablePackagesColumn::TestAvailablePackagesColumn(QObject* parent) :
    QObject(parent),
    main_window_view(new QWidget)
{
    main_window_view.init();
    QTestEventLoop::instance().enterLoop(1);
}


void TestAvailablePackagesColumn::availableColumnLabelHasProperContent()
{
    QCOMPARE(main_window_view.m_ui.accessible_packages->text(), QString("AVAILABLE TO INSTALL"));
}


void TestAvailablePackagesColumn::showAvailableColumnPreview()
{
    QTest::mouseClick(&*main_window_view.m_ui.console_view_install, Qt::LeftButton);
    qDebug() << main_window_view.m_ui.console_view_install->checkState();
    QVERIFY(!main_window_view.m_ui.available_preview_area->isHidden());
}


void TestAvailablePackagesColumn::hideAvailableColumnPreview()
{
    QTest::mouseClick(&*main_window_view.m_ui.console_view_install, Qt::LeftButton);
    QTest::mouseClick(&*main_window_view.m_ui.console_view_install, Qt::LeftButton);
    qDebug() << main_window_view.m_ui.console_view_install->checkState();
    QVERIFY(main_window_view.m_ui.available_preview_area->isHidden());
}


void TestAvailablePackagesColumn::availableColumnPreviewHasDefaultStyle()
{
    QCOMPARE(main_window_view.m_ui.text_browser_tab_install->styleSheet(), defaultStylesheet);
}


void TestAvailablePackagesColumn::availableColumnPreviewReadOnly()
{
    QVERIFY(main_window_view.m_ui.text_browser_tab_install->isReadOnly());
}


void TestAvailablePackagesColumn::searchCheckboxDisabledWithoutPackages()
{
    QVERIFY(!main_window_view.m_ui.search_available_packages_checkbox->isEnabled());
}


void TestAvailablePackagesColumn::searchCheckboxEnabledWithPackages()
{
    main_window_view.m_ui.available_packages_list->addItems(QStringList() << "a52dec-0.7.4-12.1 [cachyos-v3]" << "alsa-utils-1.2.8-1.1 [extra-x86-64-v3]");
    QVERIFY(main_window_view.m_ui.search_available_packages_checkbox->isEnabled());
}


void TestAvailablePackagesColumn::searchInputOptionVisibleAfterButtonCheck()
{
    main_window_view.m_ui.available_packages_list->addItems(QStringList() << "a52dec-0.7.4-12.1 [cachyos-v3]" << "alsa-utils-1.2.8-1.1 [extra-x86-64-v3]");
    QTest::mouseClick(&*main_window_view.m_ui.search_available_packages_checkbox, Qt::LeftButton);
    QVERIFY(!main_window_view.m_ui.search_available_packages_lineedit->isHidden());
}


void TestAvailablePackagesColumn::reversedSortOptionVisibleAfterButtonCheck()
{
    main_window_view.m_ui.available_packages_list->addItems(QStringList() << "a52dec-0.7.4-12.1 [cachyos-v3]" << "alsa-utils-1.2.8-1.1 [extra-x86-64-v3]");
    QTest::mouseClick(&*main_window_view.m_ui.search_available_packages_checkbox, Qt::LeftButton);
    QVERIFY(!main_window_view.m_ui.sort_available_packages->isHidden());
}


void TestAvailablePackagesColumn::searchInputOptionHiddenAfterButtonUncheck()
{
    main_window_view.m_ui.available_packages_list->addItems(QStringList() << "a52dec-0.7.4-12.1 [cachyos-v3]" << "alsa-utils-1.2.8-1.1 [extra-x86-64-v3]");
    QTest::mouseClick(&*main_window_view.m_ui.search_available_packages_checkbox, Qt::LeftButton);
    QTest::mouseClick(&*main_window_view.m_ui.search_available_packages_checkbox, Qt::LeftButton);
    QVERIFY(main_window_view.m_ui.search_available_packages_lineedit->isHidden());
}


void TestAvailablePackagesColumn::reversedSortOptionHiddenAfterButtonUncheck()
{
    main_window_view.m_ui.available_packages_list->addItems(QStringList() << "a52dec-0.7.4-12.1 [cachyos-v3]" << "alsa-utils-1.2.8-1.1 [extra-x86-64-v3]");
    QTest::mouseClick(&*main_window_view.m_ui.search_available_packages_checkbox, Qt::LeftButton);
    QTest::mouseClick(&*main_window_view.m_ui.search_available_packages_checkbox, Qt::LeftButton);
    QVERIFY(main_window_view.m_ui.sort_available_packages->isHidden());
}


void TestAvailablePackagesColumn::installButtonDisabledOnStart()
{
    QVERIFY(!main_window_view.m_ui.install_packages_button->isEnabled());
}


void TestAvailablePackagesColumn::installButtonEnabledAfterPackageCheck()
{
    QString package_content1 = package_content_a52dec;
    QScopedPointer<MockSiPackage> package1(new MockSiPackage(package_content1));
    main_window_view.m_ui.available_packages_list->addItem(package1.get());
    package1->setCheckState(Qt::Checked);
    QVERIFY(main_window_view.m_ui.install_packages_button->isEnabled());
}


void TestAvailablePackagesColumn::installButtonDisabledAfterPackageUncheck()
{
    QString package_content1 = package_content_a52dec;
    QScopedPointer<MockSiPackage> package1(new MockSiPackage(package_content1));
    main_window_view.m_ui.available_packages_list->addItem(package1.get());
    package1->setCheckState(Qt::Unchecked);
    QVERIFY(!main_window_view.m_ui.install_packages_button->isEnabled());
}


void TestAvailablePackagesColumn::installButtonDisabledAfterPackagesRemove()
{
    QString package_content1 = package_content_a52dec;
    QScopedPointer<MockSiPackage> package1(new MockSiPackage(package_content1));
    main_window_view.m_ui.available_packages_list->addItem(package1.get());
    package1->setCheckState(Qt::Checked);
    main_window_view.m_ui.available_packages_list->removeItemWidget(package1.get());
    package1.reset(nullptr);
    qDebug() << "Columns has " << main_window_view.m_ui.available_packages_list->count() << "packages";
    QVERIFY(!main_window_view.m_ui.install_packages_button->isEnabled());
}


void TestAvailablePackagesColumn::packagesOrderIsReversedAfterButtonCheck()
{
   auto column = QSharedPointer<MockAvailablePackagesColumn>(new MockAvailablePackagesColumn(main_window_view.m_ui.available_packages_list, main_window_view.m_ui.search_available_packages_lineedit, &main_window_view), &QObject::deleteLater);
   disconnect(main_window_view.m_ui.sort_available_packages, &QCheckBox::toggled, main_window_view.available_packages_column.data(), &InstalledPackagesColumn::sort);
   connect(main_window_view.m_ui.sort_available_packages, &QCheckBox::toggled, column.data(), &MockAvailablePackagesColumn::sort);
   column->fill();
   QTest::mouseClick(&*main_window_view.m_ui.sort_available_packages, Qt::LeftButton);
   qDebug() << "Sort button checkstate: " << main_window_view.m_ui.sort_available_packages->checkState();
   auto first_package = dynamic_cast<SiPackage*>(main_window_view.m_ui.available_packages_list->findItems("*", Qt::MatchWildcard).constFirst());
   auto last_package = dynamic_cast<SiPackage*>(main_window_view.m_ui.available_packages_list->findItems("*", Qt::MatchWildcard).constLast());
   disconnect(main_window_view.m_ui.sort_available_packages, &QCheckBox::toggled, column.data(), &MockAvailablePackagesColumn::sort);
   QCOMPARE(last_package->text(), "a52dec-0.7.4-12.1 [cachyos-v3]");
   QCOMPARE(first_package->text(), "alsa-utils-1.2.8-1.1 [extra-x86-64-v3]");
}


void TestAvailablePackagesColumn::packageOrderIsAlphabeticallByDefault()
{
    auto column = QSharedPointer<MockAvailablePackagesColumn>(new MockAvailablePackagesColumn(main_window_view.m_ui.available_packages_list, main_window_view.m_ui.search_available_packages_lineedit, &main_window_view), &QObject::deleteLater);
    column->fill();
    auto first_package = dynamic_cast<SiPackage*>(main_window_view.m_ui.available_packages_list->findItems("*", Qt::MatchWildcard).constFirst());
    auto last_package = dynamic_cast<SiPackage*>(main_window_view.m_ui.available_packages_list->findItems("*", Qt::MatchWildcard).constLast());
    disconnect(main_window_view.m_ui.sort_available_packages, &QCheckBox::toggled, column.data(), &MockAvailablePackagesColumn::sort);
    QCOMPARE(first_package->text(), "a52dec-0.7.4-12.1 [cachyos-v3]");
    QCOMPARE(last_package->text(), "alsa-utils-1.2.8-1.1 [extra-x86-64-v3]");
}


void TestAvailablePackagesColumn::checkedPackageIsStillCheckedAfterTextInputClear()
{
    auto column = QSharedPointer<MockAvailablePackagesColumn>(new MockAvailablePackagesColumn(main_window_view.m_ui.available_packages_list, main_window_view.m_ui.search_available_packages_lineedit, &main_window_view), &QObject::deleteLater);
    column->fill();
    QTest::keyClicks(&*main_window_view.m_ui.search_available_packages_lineedit, "a52");
    auto items = main_window_view.m_ui.available_packages_list->findItems("*", Qt::MatchWildcard);
    qDebug() << "count after filter: " << main_window_view.m_ui.available_packages_list->findItems("*", Qt::MatchWildcard).count();
    items.first()->setCheckState(Qt::Checked);
    qDebug() << "checkstate: " << items.first()->checkState();
    QTest::keyClicks(&*main_window_view.m_ui.search_available_packages_lineedit, "");
    auto itemsAfterClear = main_window_view.m_ui.available_packages_list->findItems("a52", Qt::MatchStartsWith);
    QCOMPARE(itemsAfterClear.first()->checkState(), Qt::Checked);
}


void TestAvailablePackagesColumn::textInputSortBya52IsEqualToOne()
{
    auto column = QSharedPointer<MockAvailablePackagesColumn>(new MockAvailablePackagesColumn(main_window_view.m_ui.available_packages_list, main_window_view.m_ui.search_available_packages_lineedit, &main_window_view), &QObject::deleteLater);
    column->fill();
    QTest::keyClicks(&*main_window_view.m_ui.search_available_packages_lineedit, "a52");
    QCOMPARE(main_window_view.m_ui.available_packages_list->findItems("*", Qt::MatchWildcard).count(), 1);
}


void TestAvailablePackagesColumn::textInputSortByaaIsEqualToZero()
{
    auto column = QSharedPointer<MockAvailablePackagesColumn>(new MockAvailablePackagesColumn(main_window_view.m_ui.available_packages_list, main_window_view.m_ui.search_available_packages_lineedit, &main_window_view), &QObject::deleteLater);
    column->fill();
    QTest::keyClicks(&*main_window_view.m_ui.search_available_packages_lineedit, "aa");
    QCOMPARE(main_window_view.m_ui.available_packages_list->findItems("*", Qt::MatchWildcard).count(), 0);
}


void TestAvailablePackagesColumn::animationsRunOnStart()
{
    QVERIFY(main_window_view.spinning_animation->isAnimationRunning());
}


void TestAvailablePackagesColumn::animationWidgetIsVisible()
{
    QVERIFY(!main_window_view.m_ui.installation_spinning_widget->isHidden());
}


void TestAvailablePackagesColumn::packagesListIsHiddenOnStart()
{
    QVERIFY(main_window_view.m_ui.available_packages_list->isHidden());
}


void TestAvailablePackagesColumn::animationIsHiddenAfterSignalSend()
{
    emit main_window_view.availablePackagesFillEnded();
    QVERIFY(main_window_view.m_ui.installation_spinning_widget->isHidden());
}


void TestAvailablePackagesColumn::notEmptyPackagesListIsVisibleAfterSignalSend()
{
    auto column = QSharedPointer<MockAvailablePackagesColumn>(new MockAvailablePackagesColumn(main_window_view.m_ui.available_packages_list, main_window_view.m_ui.search_available_packages_lineedit, &main_window_view), &QObject::deleteLater);
    column->fill();
    emit main_window_view.availablePackagesFillEnded();
    QVERIFY(!main_window_view.m_ui.available_packages_list->isHidden());
}


void TestAvailablePackagesColumn::titleIsVisibleWhenPackagesListIsEmptyAfterSignalSend()
{
    emit main_window_view.availablePackagesFillEnded();
    QCOMPARE(main_window_view.m_ui.accessible_packages->text(), QString("Something went wrong. Try to refresh"));
}


void TestAvailablePackagesColumn::cleanup()
{
    connect(main_window_view.m_ui.sort_available_packages, &QCheckBox::toggled, main_window_view.available_packages_column.data(), &InstalledPackagesColumn::sort);
    main_window_view.m_ui.available_packages_list->clear();
    main_window_view.m_ui.search_available_packages_lineedit->clear();
    main_window_view.m_ui.console_view_install->setCheckState(Qt::Unchecked);
    main_window_view.m_ui.search_available_packages_checkbox->setCheckState(Qt::Unchecked);
    main_window_view.m_ui.search_available_packages_checkbox->setDisabled(true);
    main_window_view.m_ui.install_packages_button->setEnabled(false);
    main_window_view.m_ui.sort_available_packages->setCheckState(Qt::Unchecked);

    while(main_window_view.m_ui.available_packages_list->count() > 0)
    {
        if (main_window_view.m_ui.available_packages_list->item(0))
            delete main_window_view.m_ui.available_packages_list->takeItem(0);
    }
}
