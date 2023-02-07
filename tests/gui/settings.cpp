#include "packagescolumnfixtures.h"

#include "settings.h"
#include <QApplication>
#include <QtTest/QtTest>
#include <gtest/gtest.h>
#include <QWidget>


class MockSettings : public Settings
{
    Q_OBJECT

public:
    MockSettings(MainWindow* main_window) :
        Settings(main_window)
    {
        // ...
    }

     friend class TestSettingsWindow;
};


class TestSettingsWindow : public QObject
{
    Q_OBJECT

public:
    TestSettingsWindow(QObject* parent = nullptr);

private slots:
    void generalDefaultSettingsAreCorrectlyIntroduced();
    void previewsAppearanceDefaultSettingsAreCorrectlyIntroduced();
    void availablePackagesInfoDefaultSettingsAreCorrectlyIntroduced();
    void selectedPackagesInfoDefaultSettingsAreCorrectlyIntroduced();
    void logsDefaultSettingsAreCorrectlyIntroduced();

    void cleanup();

private:
    MockMainWindow main_window;
    //MockMainWindowView main_window_view;
    MockSettings settings;
};


TestSettingsWindow::TestSettingsWindow(QObject* parent) :
    QObject(parent),
    main_window(),
    //main_window_view(new QWidget),
    settings(&main_window)
{
    //main_window.prepareProcess(QSharedPointer<MockProcess>(new MockProcess(main_window.actions_access_checker, &main_window)));
    //main_window.prepareMainWindowView(&main_window_view);
    //main_window.setCentralWidget(&main_window_view);
    //main_window.run();
    QTestEventLoop::instance().enterLoop(1);
}


void TestSettingsWindow::generalDefaultSettingsAreCorrectlyIntroduced()
{
    settings.enableDefaultButton();
    QTest::mouseClick(&*settings.button(QDialogButtonBox::StandardButton::RestoreDefaults), Qt::LeftButton);
    QCOMPARE(settings.general_settings.kcfg_history_store_time_in_days->value(), 0);
    QCOMPARE(settings.general_settings.kcfg_history_file_size_limit_in_Mb->value(), 5);
    QCOMPARE(settings.general_settings.kcfg_internet_reconnection_time_in_minutes->value(), 1);
    QCOMPARE(settings.general_settings.kcfg_update_check_time_in_days->value(), 0);
    QCOMPARE(settings.general_settings.kcfg_update_check_time_in_hours->value(), 6);
    QCOMPARE(settings.general_settings.kcfg_update_check_time_in_minutes->value(), 0);
    QVERIFY(!settings.general_settings.kcfg_overwrite_full_history_file->isChecked());
    QVERIFY(!settings.general_settings.kcfg_use_system_tray_icon->isChecked());
}


void TestSettingsWindow::previewsAppearanceDefaultSettingsAreCorrectlyIntroduced()
{
    settings.enableDefaultButton();
    QTest::mouseClick(&*settings.button(QDialogButtonBox::StandardButton::RestoreDefaults), Qt::LeftButton);
    QCOMPARE(settings.previews_appearance_settings.kcfg_background_preview_color->color(), QColor(Qt::black));
    QCOMPARE(settings.previews_appearance_settings.kcfg_preview_font_color->color(), QColor(Qt::white));
    QCOMPARE(settings.previews_appearance_settings.kcfg_preview_font_family->currentFont().family(), QString("Noto Sans"));
    QCOMPARE(settings.previews_appearance_settings.kcfg_preview_font_size->value(), 15);
}


void TestSettingsWindow::availablePackagesInfoDefaultSettingsAreCorrectlyIntroduced()
{
    settings.enableDefaultButton();
    QTest::mouseClick(&*settings.button(QDialogButtonBox::StandardButton::RestoreDefaults), Qt::LeftButton);
    settings.updateWidgetsDefault();
    settings.packages_info_settings.packages_info_selector->availableListWidget()->findItems("*", Qt::MatchWildcard);
    QStringList list_packages;
    for(const auto& available_item : settings.packages_info_settings.packages_info_selector->availableListWidget()->findItems("*", Qt::MatchWildcard))
        list_packages.append(available_item->text());

    QCOMPARE(list_packages.join(','), QString("Architecture,URL,Licenses,Groups,Provides,Optional Deps,RequiredBy,Optional For,Conflicts With,"
                                              "Replaces,Installed Size,Packager,Build Date,Install Date,Install Reason,Install Script,Validated By"));
}


void TestSettingsWindow::selectedPackagesInfoDefaultSettingsAreCorrectlyIntroduced()
{
    settings.enableDefaultButton();
    QTest::mouseClick(&*settings.button(QDialogButtonBox::StandardButton::RestoreDefaults), Qt::LeftButton);
    settings.updateWidgetsDefault();
    settings.packages_info_settings.packages_info_selector->availableListWidget()->findItems("*", Qt::MatchWildcard);
    QStringList list_packages;
    for(const auto& available_item : settings.packages_info_settings.packages_info_selector->selectedListWidget()->findItems("*", Qt::MatchWildcard))
        list_packages.append(available_item->text());

    QCOMPARE(list_packages.join(','), QString("Name,Value,Description,Depends On"));
}


void TestSettingsWindow::logsDefaultSettingsAreCorrectlyIntroduced()
{
    settings.enableDefaultButton();
    QTest::mouseClick(&*settings.button(QDialogButtonBox::StandardButton::RestoreDefaults), Qt::LeftButton);
    QVERIFY(settings.logs_settings.kcfg_save_logs_into_file->isChecked());
    QCOMPARE(settings.logs_settings.kcfg_logs_filename->text(), QString("logs.txt"));
    QCOMPARE(settings.logs_settings.kcfg_logs_filepath->text(), QString("~/.config/pak-gui"));
    QVERIFY(!settings.logs_settings.kcfg_show_debug->isChecked());
    QVERIFY(!settings.logs_settings.kcfg_hide_info_logs->isChecked());
}


void TestSettingsWindow::cleanup()
{

}

QTEST_MAIN(TestSettingsWindow)
#include "settings.moc"
