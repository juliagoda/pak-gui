#include "installedpackagescolumn.h"
#include "mainwindowview.h"
#include "qipackage.h"
#include "qnamespace.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>

const QString package_content_a52dec = "Name            : a52dec\n"
                                       "Version         : 0.7.4-12.1\n"
                                       "Description     : A free library for decoding ATSC A/52 streams\n"
                                       "Architecture    : x86_64\n"
                                       "URL             : http://liba52.sourceforge.net/\n"
                                       "Licenses        : GPL2\n"
                                       "Groups          : None\n"
                                       "Provides        : None\n"
                                       "Depends On      : glibc\n"
                                       "Optional Deps   : None\n"
                                       "Required By     : gst-plugins-ugly  mplayer  vlc\n"
                                       "Optional For    : None\n"
                                       "Conflicts With  : None\n"
                                       "Replaces        : None\n"
                                       "Installed Size  : 130,58 KiB\n"
                                       "Packager        : ALHP x86-64-v3 <alhp@harting.dev>\n"
                                       "Build Date      : wto, 27 gru 2022, 01:30:08\n"
                                       "Install Date    : pon, 2 sty 2023, 13:19:58\n"
                                       "Install Reason  : Installed as a dependency for another package\n"
                                       "Install Script  : No\n";

const QString package_content_alsa_utils = "Name            : alsa-utils\n"
                                           "Version         : 1.2.8-1.1\n"
                                           "Description     : Advanced Linux Sound Architecture - Utilities\n"
                                           "Architecture    : x86_64\n"
                                           "URL             : https://www.alsa-project.org\n"
                                           "Licenses        : GPL2\n"
                                           "Groups          : None\n"
                                           "Provides        : None\n"
                                           "Depends On      : glibc  pciutils  psmisc  libasound.so=2-64\n"
                                           "                  libatopology.so=2-64  libformw.so=6-64  libmenuw.so=6-64\n"
                                           "                  libncursesw.so=6-64  libpanelw.so=6-64  libsamplerate.so=0-64\n"
                                           "Optional Deps   : fftw: for alsabat [installed]\n"
                                           "Required By     : None\n"
                                           "Optional For    : None\n"
                                           "Conflicts With  : None\n"
                                           "Replaces        : None\n"
                                           "Installed Size  : 2,34 MiB\n"
                                           "Packager        : ALHP x86-64-v3 <alhp@harting.dev>\n"
                                           "Build Date      : pią, 28 paź 2022, 11:01:32\n"
                                           "Install Date    : pon, 31 paź 2022, 18:26:51\n"
                                           "Install Reason  : Explicitly installed\n"
                                           "Install Script  : No\n";


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


class MockMainWindowView : public MainWindowView
{
    Q_OBJECT

public:
    MockMainWindowView();
    friend class TestInstalledPackagesColumn;

protected:
    void initColumns() override;
};

MockMainWindowView::MockMainWindowView() :
    MainWindowView(new QWidget)
{

}


void MockMainWindowView::initColumns()
{
    available_packages_column = QSharedPointer<AvailablePackagesColumn>(new AvailablePackagesColumn(m_ui.available_packages_list, m_ui.search_available_packages_lineedit, this), &QObject::deleteLater);
    installed_packages_column = QSharedPointer<MockInstalledPackagesColumn>(new MockInstalledPackagesColumn(m_ui.installed_packages_list, m_ui.search_installed_packages_lineedit, this), &QObject::deleteLater);
    updated_packages_column = QSharedPointer<UpdatedPackagesColumn>(new UpdatedPackagesColumn(m_ui.packages_to_update_list, m_ui.search_packages_to_update_lineedit, this), &QObject::deleteLater);
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
    void uninstallButtonEnabledAfterPackagesRemove();
    void packagesOrderIsReversedAfterButtonCheck();

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
    QCOMPARE(main_window_view.m_ui.text_browser_tab_uninstall->styleSheet(),
             QString("color: white;\nbackground-color: black;\nfont-family: Lucida Console,Lucida Sans Typewriter,monaco,Bitstream Vera Sans Mono,monospace;\npadding: 3px;"));
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


void TestInstalledPackagesColumn::uninstallButtonEnabledAfterPackagesRemove()
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
   auto first_package = dynamic_cast<QiPackage*>(main_window_view.m_ui.installed_packages_list->findItems("*", Qt::MatchWildcard).first());
   auto last_package = dynamic_cast<QiPackage*>(main_window_view.m_ui.installed_packages_list->findItems("*", Qt::MatchWildcard).last());
   disconnect(main_window_view.m_ui.sort_installed_packages, &QCheckBox::toggled, column.data(), &MockInstalledPackagesColumn::sort);
   QCOMPARE(last_package->text(), "a52dec-0.7.4-12.1");
   QCOMPARE(first_package->text(), "alsa-utils-1.2.8-1.1");
}


void TestInstalledPackagesColumn::cleanup()
{
    connect(main_window_view.m_ui.sort_installed_packages, &QCheckBox::toggled, main_window_view.installed_packages_column.data(), &InstalledPackagesColumn::sort);
    main_window_view.m_ui.installed_packages_list->clear();
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
#include "mainwindow.moc"
