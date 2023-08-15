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

#include "mainwindowtest.h"
#include "logger.h"

#include <KLocalizedString>
#include <KLed>


TestMainWindow::TestMainWindow(QObject* parent) :
    QObject(parent),
    main_window(),
    main_window_view(new QWidget)
{
    main_window.prepareProcess(QSharedPointer<MockProcess>(new MockProcess(main_window.actions_access_checker, &main_window)));
    main_window.prepareMainWindowView(&main_window_view);
    main_window.setCentralWidget(&main_window_view);
    main_window.run();
    QTestEventLoop::instance().enterLoop(1);
}


void TestMainWindow::ledLabelsContainCorrectTexts()
{
   QCOMPARE(main_window_view.m_ui.repo_led_label->text(), i18n("Repositories"));
   QCOMPARE(main_window_view.m_ui.aur_led_label->text(), i18n("AUR"));
   QCOMPARE(main_window_view.m_ui.polaur_led_label->text(), i18n("POLAUR"));
}


void TestMainWindow::ledLabelsContainCorrectTooltips()
{
    QCOMPARE(main_window_view.m_ui.repo_led_label->toolTip(), i18n("Internet connection state"));
    QCOMPARE(main_window_view.m_ui.aur_led_label->toolTip(), i18n("Internet connection state and auracle-git package presence"));
    QCOMPARE(main_window_view.m_ui.polaur_led_label->toolTip(), i18n("Internet connection state and git package presence"));
}


void TestMainWindow::ledAreOffByDefault()
{
    QCOMPARE(main_window_view.m_ui.repos_kled->state(), KLed::State::Off);
    QCOMPARE(main_window_view.m_ui.aur_kled->state(), KLed::State::Off);
    QCOMPARE(main_window_view.m_ui.polaur_kled->state(), KLed::State::Off);
}


void TestMainWindow::repositoriesLedIsOnWhenOnline()
{
    emit main_window.actions_access_checker->internetAccessChanged(true);
    QCOMPARE(main_window_view.m_ui.repos_kled->state(), KLed::State::On);
}


void TestMainWindow::aurLedIsOnWhenAuracleGitInstalledAndIsOnline()
{
    emit main_window.actions_access_checker->internetAccessChanged(true);
    emit main_window.actions_access_checker->auracleAccessChanged(true);
    QCOMPARE(main_window_view.m_ui.aur_kled->state(), KLed::State::On);
}


void TestMainWindow::polaurLedIsOnWhenGitInstalledAndIsOnline()
{
    emit main_window.actions_access_checker->internetAccessChanged(true);
    emit main_window.actions_access_checker->gitAccessChanged(true);
    QCOMPARE(main_window_view.m_ui.polaur_kled->state(), KLed::State::On);
}


void TestMainWindow::noInternetConnectionTextIsVisibleWhenInternetConnectionIsOff()
{
    emit main_window.actions_access_checker->internetAccessChanged(false);
    QCOMPARE(main_window_view.m_ui.packages_to_update_label->text(), i18n("No internet connection"));
    QCOMPARE(main_window_view.m_ui.accessible_packages->text(), i18n("No internet connection"));
}


void TestMainWindow::onlineActionsAreDisabledWhenInternetConnectionIsOff()
{
    emit main_window.actions_access_checker->internetAccessChanged(false);
    QVERIFY(!main_window.update_action.data()->isEnabled());
    QVERIFY(!main_window.download_action.data()->isEnabled());
    QVERIFY(!main_window.update_all_action.data()->isEnabled());
    QVERIFY(!main_window.update_mirrors_action.data()->isEnabled());
    QVERIFY(!main_window.search_action.data()->isEnabled());
}


void TestMainWindow::offlineActionsAreEnabledWhenInternetConnectionIsOff()
{
    emit main_window.actions_access_checker->internetAccessChanged(false);
    QVERIFY(main_window.refresh_action.data()->isEnabled());
    QVERIFY(main_window.clean_action.data()->isEnabled());
    QVERIFY(main_window.print_statistics_action.data()->isEnabled());
}


void TestMainWindow::searchAndPreviewsWidgetsAreHiddenWhenInternetConnectionIsOff()
{
    // only for packages to update and available one
    emit main_window.actions_access_checker->internetAccessChanged(false);
    QVERIFY(main_window_view.m_ui.updated_preview_area->isHidden());
    QVERIFY(main_window_view.m_ui.available_preview_area->isHidden());
    QVERIFY(main_window_view.m_ui.sort_available_packages->isHidden());
    QVERIFY(main_window_view.m_ui.sort_packages_to_update->isHidden());
    QVERIFY(main_window_view.m_ui.search_packages_to_update_lineedit->isHidden());
    QVERIFY(main_window_view.m_ui.search_available_packages_lineedit->isHidden());
    QVERIFY(main_window_view.m_ui.available_packages_list->isHidden());
    QVERIFY(main_window_view.m_ui.packages_to_update_list->isHidden());
}


void TestMainWindow::actionsAreDisabledAfterInitializationStart()
{
    emit main_window.main_window_view->initStarted();
    QVERIFY(!main_window.update_action.data()->isEnabled());
    QVERIFY(!main_window.download_action.data()->isEnabled());
    QVERIFY(!main_window.update_all_action.data()->isEnabled());
    QVERIFY(!main_window.update_mirrors_action.data()->isEnabled());
    QVERIFY(!main_window.search_action.data()->isEnabled());
    QVERIFY(!main_window.refresh_action.data()->isEnabled());
    QVERIFY(!main_window.clean_action.data()->isEnabled());
    QVERIFY(!main_window.print_statistics_action.data()->isEnabled());
}


void TestMainWindow::actionsAreEnabledAfterInitializationEnd()
{
    emit main_window.main_window_view->initEnded();
    emit main_window.actions_access_checker->reflectorAccessChanged(true);
    QVERIFY(main_window.update_action.data()->isEnabled());
    QVERIFY(main_window.download_action.data()->isEnabled());
    QVERIFY(main_window.update_all_action.data()->isEnabled());
    QVERIFY(main_window.update_mirrors_action.data()->isEnabled());
    QVERIFY(main_window.search_action.data()->isEnabled());
    QVERIFY(main_window.refresh_action.data()->isEnabled());
    QVERIFY(main_window.clean_action.data()->isEnabled());
    QVERIFY(main_window.print_statistics_action.data()->isEnabled());
}


void TestMainWindow::updateMirrorsActionIsDisabledWhenReflectorPackageIsNotDetected()
{
    emit main_window.actions_access_checker->reflectorAccessChanged(false);
    QVERIFY(!main_window.update_mirrors_action.data()->isEnabled());
}


void TestMainWindow::updateMirrorsActionIsEnabledWhenReflectorPackageIsDetected()
{
    emit main_window.actions_access_checker->reflectorAccessChanged(true);
    QVERIFY(main_window.update_mirrors_action.data()->isEnabled());
}


void TestMainWindow::viewProgressCheckboxIsHiddenByDefault()
{
   QVERIFY(main_window_view.m_ui.progress_view_checkbox->isHidden());
}


void TestMainWindow::viewProgressCheckboxIsVisibleDuringClean()
{
   emit main_window.process->acceptedTask(Process::Task::Clean);
   QVERIFY(!main_window_view.m_ui.progress_view_checkbox->isHidden());

   main_window_view.progress_view.data()->removeProgressView(main_window_view.generated_previews_map.value(Process::Task::Clean));
   main_window_view.generated_previews_map.remove(Process::Task::Clean);
}


void TestMainWindow::viewProgressCheckboxIsVisibleDuringMirrorsUpdate()
{
   emit main_window.process->acceptedTask(Process::Task::MirrorsUpdate);
   QVERIFY(!main_window_view.m_ui.progress_view_checkbox->isHidden());

   main_window_view.progress_view.data()->removeProgressView(main_window_view.generated_previews_map.value(Process::Task::MirrorsUpdate));
   main_window_view.generated_previews_map.remove(Process::Task::MirrorsUpdate);
}


void TestMainWindow::viewProgressCheckboxIsVisibleDuringVcsPackagesPrint()
{
   emit main_window.process->acceptedTask(Process::Task::PrintVCSPackages);
   QVERIFY(!main_window_view.m_ui.progress_view_checkbox->isHidden());

   main_window_view.progress_view.data()->removeProgressView(main_window_view.generated_previews_map.value(Process::Task::PrintVCSPackages));
   main_window_view.generated_previews_map.remove(Process::Task::PrintVCSPackages);
}


void TestMainWindow::viewProgressCheckboxIsVisibleDuringInstalledPackagesUpdate()
{
   emit main_window.process->acceptedTask(Process::Task::UpdateInstalledPackages);
   QVERIFY(!main_window_view.m_ui.progress_view_checkbox->isHidden());

   main_window_view.progress_view.data()->removeProgressView(main_window_view.generated_previews_map.value(Process::Task::UpdateInstalledPackages));
   main_window_view.generated_previews_map.remove(Process::Task::UpdateInstalledPackages);
}


void TestMainWindow::spinningAnimationForSideTaskIsVisibleDuringClean()
{
   emit main_window.process->acceptedTask(Process::Task::Clean);
   QVERIFY(!main_window_view.m_ui.actions_spinning_animation_label->isHidden());
   QVERIFY(main_window_view.spinning_animation->isSmallAnimationRunning());

   main_window_view.progress_view.data()->removeProgressView(main_window_view.generated_previews_map.value(Process::Task::Clean));
   main_window_view.generated_previews_map.remove(Process::Task::Clean);
}


void TestMainWindow::spinningAnimationForSideTaskIsVisibleDuringMirrorsUpdate()
{
   emit main_window.process->acceptedTask(Process::Task::MirrorsUpdate);
   QVERIFY(!main_window_view.m_ui.actions_spinning_animation_label->isHidden());
   QVERIFY(main_window_view.spinning_animation->isSmallAnimationRunning());

   main_window_view.progress_view.data()->removeProgressView(main_window_view.generated_previews_map.value(Process::Task::MirrorsUpdate));
   main_window_view.generated_previews_map.remove(Process::Task::MirrorsUpdate);
}


void TestMainWindow::spinningAnimationForSideTaskIsVisibleDuringVcsPackagesPrint()
{
   emit main_window.process->acceptedTask(Process::Task::PrintVCSPackages);
   QVERIFY(!main_window_view.m_ui.actions_spinning_animation_label->isHidden());
   QVERIFY(main_window_view.spinning_animation->isSmallAnimationRunning());

   main_window_view.progress_view.data()->removeProgressView(main_window_view.generated_previews_map.value(Process::Task::PrintVCSPackages));
   main_window_view.generated_previews_map.remove(Process::Task::PrintVCSPackages);
}


void TestMainWindow::spinningAnimationForSideTaskIsVisibleDuringInstalledPackagesUpdate()
{
   emit main_window.process->acceptedTask(Process::Task::UpdateInstalledPackages);
   QVERIFY(!main_window_view.m_ui.actions_spinning_animation_label->isHidden());
   QVERIFY(main_window_view.spinning_animation->isSmallAnimationRunning());

   main_window_view.progress_view.data()->removeProgressView(main_window_view.generated_previews_map.value(Process::Task::UpdateInstalledPackages));
   main_window_view.generated_previews_map.remove(Process::Task::UpdateInstalledPackages);
}


void TestMainWindow::viewProgressCheckboxIsHiddenAfterEndOfTasks()
{
   emit main_window.process->acceptedTask(Process::Task::Clean);
    qDebug() << "Amount of side tasks: " << main_window_view.generated_previews_map.count();
   emit main_window.process->finished(Process::Task::Clean, 0, QProcess::ExitStatus::NormalExit);
   qDebug() << "Amount of side tasks after finish: " << main_window_view.generated_previews_map.count();
   QVERIFY(main_window_view.m_ui.progress_view_checkbox->isHidden());
}


void TestMainWindow::spinningAnimationForSideTaskIsStoppedAfterEndOfTasks()
{
    emit main_window.process->acceptedTask(Process::Task::Clean);
    emit main_window.process->finished(Process::Task::Clean, 0, QProcess::ExitStatus::NormalExit);
    QVERIFY(!main_window_view.spinning_animation->isSmallAnimationRunning());
    QVERIFY(main_window_view.m_ui.actions_spinning_animation_label->isHidden());
}


void TestMainWindow::cleanup()
{
   main_window_view.m_ui.progress_view_checkbox->hide();
   main_window_view.m_ui.actions_spinning_animation_label->hide();
   emit main_window.actions_access_checker->internetAccessChanged(false);
   emit main_window.actions_access_checker->gitAccessChanged(false);
   emit main_window.actions_access_checker->aspAccessChanged(false);
   emit main_window.actions_access_checker->auracleAccessChanged(false);
   emit main_window.actions_access_checker->reflectorAccessChanged(false);
   main_window_view.generated_previews_map.clear();
}
