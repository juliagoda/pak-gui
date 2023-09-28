// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of CachyOS package manager based on "pak" application.
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

#include "mainwindowviewsignals.h"

#include "timeconverter.h"
#include "settings.h"
#include "logger.h"

#include <QtConcurrent/QtConcurrent>


MainWindowViewSignals::MainWindowViewSignals(MainWindowView* main_window_view) :
    main_window_view{main_window_view}
{
                                                                                                                       // ...
}

MainWindowViewSignals::~MainWindowViewSignals()
{
    if (!packages_timer.isNull())
        packages_timer->stop();
}


void MainWindowViewSignals::attachInputAnswerLines()
{
    QObject::connect(main_window_view->m_ui.input_for_uninstall_lineedit, &QLineEdit::textChanged, this, [this](const QString& text)
                     { text.isEmpty() ? main_window_view->m_ui.input_for_uninstall_btn->setEnabled(false) : main_window_view->m_ui.input_for_uninstall_btn->setEnabled(true); });
    QObject::connect(main_window_view->m_ui.input_for_install_lineedit, &QLineEdit::textChanged, this, [this](const QString& text)
                     { text.isEmpty() ? main_window_view->m_ui.input_for_install_btn->setEnabled(false) : main_window_view->m_ui.input_for_install_btn->setEnabled(true); });
    QObject::connect(main_window_view->m_ui.input_for_update_lineedit, &QLineEdit::textChanged, this, [this](const QString& text)
                     { text.isEmpty() ? main_window_view->m_ui.input_for_update_btn->setEnabled(false) : main_window_view->m_ui.input_for_update_btn->setEnabled(true); });
}


void MainWindowViewSignals::attachFillColumns()
{
    QtConcurrent::run([&]() {
        main_window_view->available_packages_column->fill();
        emit main_window_view->availablePackagesFillEnded();
    });

    QtConcurrent::run([&]() {
        main_window_view->installed_packages_column->fill();
        emit main_window_view->installedPackagesFillEnded();
    });
}


void MainWindowViewSignals::startPackagesCheckTimer()
{
    if (main_window_view->actions_access_checker.isNull())
        return;

    packages_timer.reset(new QTimer);
    connect(packages_timer.get(), &QTimer::timeout, main_window_view->actions_access_checker.get(), &ActionsAccessChecker::checkRequiredPackages);
    packages_timer->start(8000);
    Logger::logger()->logDebug(QStringLiteral("Required packages checker started with interval %2").arg(8000));
}


void MainWindowViewSignals::startInternetCheckTimer()
{
    if (main_window_view->internet_connection_timer.isNull() || main_window_view->actions_access_checker.isNull())
        return;

    disconnect(main_window_view->internet_connection_timer.get(), &QTimer::timeout, main_window_view->actions_access_checker.get(), &ActionsAccessChecker::checkInternetConnection);
    if (Settings::records()->internetReconnectionTimeMinutes() == 0)
        return;

    connect(main_window_view->internet_connection_timer.get(), &QTimer::timeout, main_window_view->actions_access_checker.get(), &ActionsAccessChecker::checkInternetConnection);
    int milliseconds = TimeConverter::minutesToMilliseconds(Settings::records()->internetReconnectionTimeMinutes());
    main_window_view->internet_connection_timer->start(milliseconds);
    Logger::logger()->logDebug(QStringLiteral("Internet connection checker started with interval %2").arg(milliseconds));
}


void MainWindowViewSignals::attachConnectSignalsAfterFillEnd()
{
    QObject::connect(main_window_view, &MainWindowView::availablePackagesFillEnded, main_window_view, &MainWindowView::connectSignalsForAvailablePackages);
    QObject::connect(main_window_view, &MainWindowView::installedPackagesFillEnded, main_window_view, &MainWindowView::connectSignalsForInstalledPackages);
    QObject::connect(main_window_view, &MainWindowView::packagesToUpdateFillEnded, main_window_view, &MainWindowView::connectSignalsForUpdatedPackages);
}


void MainWindowViewSignals::attachMainPreviewsVisibility()
{
    QObject::connect(main_window_view->m_ui.console_view_install, &QCheckBox::toggled, [this](bool is_checked) { if (is_checked) main_window_view->m_ui.available_preview_area->show(); else main_window_view->m_ui.available_preview_area->hide(); });
    QObject::connect(main_window_view->m_ui.console_view_uninstall, &QCheckBox::toggled, [this](bool is_checked) { if (is_checked) main_window_view->m_ui.installed_preview_area->show(); else main_window_view->m_ui.installed_preview_area->hide(); });
    QObject::connect(main_window_view->m_ui.console_view_update, &QCheckBox::toggled, [this](bool is_checked) { if (is_checked) main_window_view->m_ui.updated_preview_area->show(); else main_window_view->m_ui.updated_preview_area->hide(); });
}


void MainWindowViewSignals::attachPackagesAccess()
{
    if (!main_window_view->actions_access_checker.isNull())
    {
        QObject::connect(main_window_view->actions_access_checker.get(), &ActionsAccessChecker::internetAccessChanged, main_window_view, &MainWindowView::toggleWidgetsAccess);
        QObject::connect(main_window_view->actions_access_checker.get(), &ActionsAccessChecker::auracleAccessChanged, [this](bool is_auracle_installed){ is_auracle_installed && main_window_view->actions_access_checker->isOnline() ? main_window_view->m_ui.aur_kled->on() : main_window_view->m_ui.aur_kled->off();});
        QObject::connect(main_window_view->actions_access_checker.get(), &ActionsAccessChecker::gitAccessChanged, [this](bool is_git_installed){ is_git_installed && main_window_view->actions_access_checker->isOnline() ? main_window_view->m_ui.polaur_kled->on() : main_window_view->m_ui.polaur_kled->off();});
    }
}


void MainWindowViewSignals::attachSignalsForSidePreviews()
{
    QObject::connect(main_window_view, &MainWindowView::operationsAmountIncreased, main_window_view->m_ui.progress_view_checkbox, &QCheckBox::show);

    if (!main_window_view->progress_view.isNull())
        QObject::connect(main_window_view->progress_view.data(), &QDialog::rejected, [this](){ main_window_view->m_ui.progress_view_checkbox->setChecked(false); });

    QObject::connect(main_window_view->m_ui.progress_view_checkbox, &QCheckBox::toggled, [this](bool is_checked) { if (is_checked) { main_window_view->progress_view->resize(500, 500); main_window_view->progress_view.data()->show(); } else main_window_view->progress_view.data()->hide(); });
}


void MainWindowViewSignals::attachSignalsForProcess()
{
    QObject::connect(main_window_view->m_ui.input_for_uninstall_btn, &QPushButton::clicked, main_window_view->process.data(), [this](bool)
        { main_window_view->process->inputAnswer(main_window_view->m_ui.input_for_uninstall_lineedit->text(), Process::Task::Uninstall); });
    QObject::connect(main_window_view->m_ui.input_for_install_btn, &QPushButton::clicked, main_window_view->process.data(), [this](bool)
                     { main_window_view->process->inputAnswer(main_window_view->m_ui.input_for_install_lineedit->text(), Process::Task::Install); });
    QObject::connect(main_window_view->m_ui.input_for_update_btn, &QPushButton::clicked, main_window_view->process.data(), [this](bool)
                     { main_window_view->process->inputAnswer(main_window_view->m_ui.input_for_update_lineedit->text(), Process::Task::Update); });

    QObject::connect(main_window_view->process.data(), &Process::showInput, main_window_view, &MainWindowView::showInputWidgets);
    QObject::connect(main_window_view->process.data(), &Process::acceptedMainTask, main_window_view, &MainWindowView::showSingleAnimation, Qt::AutoConnection);
    QObject::connect(main_window_view->process.data(), &Process::acceptedMainTask, [this](Process::Task new_task)
    {
        if (new_task == Process::Task::Update ||
            new_task == Process::Task::UpdateAll)
        {
            main_window_view->current_update_process = main_window_view->process->getCurrentProcess();
            main_window_view->m_ui.abort_update_process_btn->show();
        }

        if (new_task == Process::Task::Install)
        {
            main_window_view->current_installation_process = main_window_view->process->getCurrentProcess();
            main_window_view->m_ui.abort_installation_process_btn->show();
        }

        if (new_task == Process::Task::Uninstall)
        {
            main_window_view->current_uninstallation_process = main_window_view->process->getCurrentProcess();
            main_window_view->m_ui.abort_uninstallation_process_btn->show();
        }
    });

    QObject::connect(main_window_view->process.data(), &Process::generatedOutput, main_window_view, &MainWindowView::generateOutput, Qt::AutoConnection);
    QObject::connect(main_window_view->process.data(), &Process::acceptedTask, main_window_view, &MainWindowView::generatePreview);
    QObject::connect(main_window_view->process.data(), &Process::acceptedTask, [this](){ main_window_view->spinning_animation->startSmallOnWidget(main_window_view->m_ui.actions_spinning_animation_label);  });
    QObject::connect(main_window_view->process.data(), &Process::finished, this, [this](Process::Task task, int exit_code, QProcess::ExitStatus exit_status) { main_window_view->finishProcess(task, exit_code, exit_status); }, Qt::AutoConnection);
    QObject::connect(main_window_view->process.data(), &Process::finished, [this](){ main_window_view->spinning_animation->stopSmallOnWidget(main_window_view->m_ui.actions_spinning_animation_label);  });
    QObject::connect(main_window_view->process.data(), &Process::finished, [this](Process::Task new_task, int exit_code, QProcess::ExitStatus exit_status)
    {
        if (new_task == Process::Task::Update ||
            new_task == Process::Task::UpdateAll)
        {
            main_window_view->current_update_process = nullptr;
            if (main_window_view->m_ui.abort_update_process_btn)
              main_window_view->m_ui.abort_update_process_btn->hide();
        }

        if (new_task == Process::Task::Install)
        {
            main_window_view->current_installation_process = nullptr;
            if (main_window_view->m_ui.abort_update_process_btn)
              main_window_view->m_ui.abort_installation_process_btn->hide();
        }

        if (new_task == Process::Task::Uninstall)
        {
            main_window_view->current_uninstallation_process = nullptr;
            if (main_window_view->m_ui.abort_update_process_btn)
              main_window_view->m_ui.abort_uninstallation_process_btn->hide();
        }
    });
}


void MainWindowViewSignals::attachAvailablePackagesColumn()
{
    QObject::connect(main_window_view->m_ui.sort_available_packages, &QCheckBox::toggled, main_window_view->available_packages_column.data(), &AvailablePackagesColumn::sort, Qt::AutoConnection);
    QObject::connect(main_window_view->available_packages_column.data(), &AvailablePackagesColumn::checkedPackagesCounterChanged, [this](bool has_checked_buttons) { main_window_view->m_ui.install_packages_button->setEnabled(has_checked_buttons); });
    QObject::connect(main_window_view->m_ui.install_packages_button, &QPushButton::clicked, this, [this]() { main_window_view->m_ui.text_browser_tab_install->clear(); main_window_view->process->setPackagesToUpdate(main_window_view->updated_packages_column->getCurrentPackagesCount());

    if (main_window_view->process->preparedBeforeRun(Process::Task::Install, main_window_view->available_packages_column.data()->getCheckedPackagesStringList()))
      main_window_view->process->run(Process::Task::Install, main_window_view->available_packages_column.data()->getCheckedPackagesStringList()); }, Qt::AutoConnection);

    QObject::connect(main_window_view->available_packages_column.data(), &AvailablePackagesColumn::showAbortButton, [this](QProcess* process)
    {
        main_window_view->current_installation_process = process;
        if (main_window_view->m_ui.abort_installation_process_btn)
          main_window_view->m_ui.abort_installation_process_btn->show();
    });

    QObject::connect(main_window_view->available_packages_column.data(), &AvailablePackagesColumn::hideAbortButton, [this]()
    {
        main_window_view->current_installation_process = nullptr;
        if (main_window_view->m_ui.abort_installation_process_btn)
          main_window_view->m_ui.abort_installation_process_btn->hide();
    });

    QObject::connect(main_window_view->m_ui.abort_installation_process_btn, &QPushButton::clicked, [this]()
    {
        main_window_view->abortProcessFromButton(main_window_view->current_installation_process, main_window_view->m_ui.abort_installation_process_btn);
    });

    QObject::connect(main_window_view->process.get(), &Process::acceptedUpdateAll, main_window_view, &MainWindowView::blockUpdateColumn);
    QObject::connect(main_window_view->m_ui.available_packages_list->model(), &QAbstractListModel::rowsRemoved, this, [this](){ if (main_window_view->m_ui.available_packages_list->count() == 0) main_window_view->m_ui.install_packages_button->setEnabled(false); }, Qt::AutoConnection);
    QObject::connect(main_window_view->m_ui.available_packages_list->model(), &QAbstractListModel::rowsInserted, this, [this](){ main_window_view->m_ui.search_available_packages_checkbox->setEnabled(true); }, Qt::AutoConnection);
    QObject::connect(main_window_view->m_ui.available_packages_list->model(), &QAbstractListModel::rowsRemoved, this, [this](){ if (main_window_view->m_ui.available_packages_list->count() == 0) main_window_view->m_ui.search_available_packages_checkbox->setEnabled(false); }, Qt::AutoConnection);

    QObject::connect(main_window_view->m_ui.search_available_packages_checkbox, &QCheckBox::clicked, this, [this](bool checked)
    {
        if (!checked)
        {
            main_window_view->m_ui.search_available_packages_lineedit->clear();
            if (main_window_view->m_ui.sort_available_packages->checkState() == Qt::Checked)
                main_window_view->m_ui.sort_available_packages->click();
        }
    });
}


void MainWindowViewSignals::attachInstalledPackagesColumn()
{
    QObject::connect(main_window_view->m_ui.sort_installed_packages, &QCheckBox::toggled, main_window_view->installed_packages_column.data(), &InstalledPackagesColumn::sort, Qt::AutoConnection);
    QObject::connect(main_window_view->installed_packages_column.data(), &InstalledPackagesColumn::checkedPackagesCounterChanged, this, [this](bool has_checked_buttons) { main_window_view->m_ui.uninstall_packages_button->setEnabled(has_checked_buttons); }, Qt::AutoConnection);
    QObject::connect(main_window_view->m_ui.uninstall_packages_button, &QPushButton::clicked, this, [this]() { main_window_view->m_ui.text_browser_tab_uninstall->clear();

    if (main_window_view->process->preparedBeforeRun(Process::Task::Uninstall, main_window_view->installed_packages_column.data()->getCheckedPackagesStringList()))
      main_window_view->process->run(Process::Task::Uninstall, main_window_view->installed_packages_column.data()->getCheckedPackagesStringList()); }, Qt::AutoConnection);


    QObject::connect(main_window_view->installed_packages_column.data(), &InstalledPackagesColumn::showAbortButton, [this](QProcess* process)
        {
            main_window_view->current_uninstallation_process = process;
          //if (main_window_view->m_ui.abort_uninstallation_process_btn)
          //  main_window_view->m_ui.abort_uninstallation_process_btn->show();
        });

    QObject::connect(main_window_view->installed_packages_column.data(), &InstalledPackagesColumn::hideAbortButton, [this]()
        {
            main_window_view->current_uninstallation_process = nullptr;
          if (main_window_view->m_ui.abort_uninstallation_process_btn)
            main_window_view->m_ui.abort_uninstallation_process_btn->hide();
        });

    QObject::connect(main_window_view->m_ui.abort_uninstallation_process_btn, &QPushButton::clicked, [this]()
        {
            main_window_view->abortProcessFromButton(main_window_view->current_uninstallation_process, main_window_view->m_ui.abort_uninstallation_process_btn);
        });

    QObject::connect(main_window_view->m_ui.installed_packages_list->model(), &QAbstractListModel::rowsRemoved, this, [this](){ if (main_window_view->m_ui.installed_packages_list->count() == 0) main_window_view->m_ui.uninstall_packages_button->setEnabled(false); }, Qt::AutoConnection);
    QObject::connect(main_window_view->m_ui.installed_packages_list->model(), &QAbstractListModel::rowsInserted, this, [this](){ main_window_view->m_ui.search_installed_packages_checkbox->setEnabled(true); }, Qt::AutoConnection);
    QObject::connect(main_window_view->m_ui.installed_packages_list->model(), &QAbstractListModel::rowsRemoved, this, [this](){ if (main_window_view->m_ui.installed_packages_list->count() == 0) main_window_view->m_ui.search_installed_packages_checkbox->setEnabled(false); }, Qt::AutoConnection);

    QObject::connect(main_window_view->m_ui.search_installed_packages_checkbox, &QCheckBox::clicked, this, [this](bool checked)
    {
        if (!checked)
        {
            main_window_view->m_ui.search_installed_packages_lineedit->clear();
            if (main_window_view->m_ui.sort_installed_packages->checkState() == Qt::Checked)
                main_window_view->m_ui.sort_installed_packages->click();
        }
    });
}


void MainWindowViewSignals::attachPackagesToUpdateColumn()
{
    QObject::connect(main_window_view->m_ui.sort_packages_to_update, &QCheckBox::toggled, main_window_view->updated_packages_column.data(), &UpdatedPackagesColumn::sort, Qt::AutoConnection);
    QObject::connect(main_window_view->updated_packages_column.data(), &UpdatedPackagesColumn::checkedPackagesCounterChanged, this, [this](bool has_checked_buttons) { main_window_view->m_ui.update_packages_button->setEnabled(has_checked_buttons); }, Qt::AutoConnection);
    QObject::connect(main_window_view->m_ui.update_packages_button, &QPushButton::clicked, this, [this]() { main_window_view->updated_packages_column.data()->prepareBeforeProcessRun(); }, Qt::AutoConnection);

    QObject::connect(main_window_view->updated_packages_column.data(), &UpdatedPackagesColumn::preparedList, [this](QStringList packages_list, Process::Task task, uint aur_checked_packages){ main_window_view->process->setPackagesToUpdate(packages_list.count()); main_window_view->process->setAurPackagesToUpdate(aur_checked_packages);
    main_window_view->m_ui.text_browser_tab_update->clear();
    if (main_window_view->process->preparedBeforeRun(task, packages_list))
      main_window_view->process->run(task, packages_list); });

    QObject::connect(main_window_view->updated_packages_column.data(), &UpdatedPackagesColumn::showAbortButton, [this](QProcess* process)
        {
            main_window_view->current_update_process = process;
            main_window_view->m_ui.abort_update_process_btn->show();
        });

    QObject::connect(main_window_view->updated_packages_column.data(), &UpdatedPackagesColumn::hideAbortButton, [this]()
        {
            main_window_view->current_update_process = nullptr;
            main_window_view->m_ui.abort_update_process_btn->hide();
        });

    QObject::connect(main_window_view->m_ui.abort_update_process_btn, &QPushButton::clicked, [this]()
        {
            main_window_view->abortProcessFromButton(main_window_view->current_update_process, main_window_view->m_ui.abort_update_process_btn);
        });

    QObject::connect(main_window_view->m_ui.packages_to_update_list->model(), &QAbstractListModel::rowsRemoved, this, [this](){ if (main_window_view->m_ui.packages_to_update_list->count() == 0) main_window_view->m_ui.update_packages_button->setEnabled(false); }, Qt::AutoConnection);
    QObject::connect(main_window_view->m_ui.packages_to_update_list->model(), &QAbstractListModel::rowsInserted, this, [this](){ main_window_view->m_ui.search_packages_to_update_checkbox->setEnabled(true); }, Qt::AutoConnection);
    QObject::connect(main_window_view->m_ui.packages_to_update_list->model(), &QAbstractListModel::rowsRemoved, this, [this](){ if (main_window_view->m_ui.packages_to_update_list->count() == 0) main_window_view->m_ui.search_packages_to_update_checkbox->setEnabled(false); }, Qt::AutoConnection);
    QObject::connect(main_window_view->m_ui.packages_to_update_list->model(), &QAbstractListModel::rowsInserted, this, [this](){ main_window_view->m_ui.check_all_updates_checkbox->setEnabled(true); }, Qt::AutoConnection);
    QObject::connect(main_window_view->m_ui.packages_to_update_list->model(), &QAbstractListModel::rowsRemoved, this, [this](){ if (main_window_view->m_ui.packages_to_update_list->count() == 0) main_window_view->m_ui.check_all_updates_checkbox->setEnabled(false); }, Qt::AutoConnection);

    QObject::connect(main_window_view->m_ui.search_packages_to_update_checkbox, &QCheckBox::clicked, this, [this](bool checked)
    {
        if (!checked)
        {
            main_window_view->m_ui.search_packages_to_update_lineedit->clear();
            if (main_window_view->m_ui.sort_packages_to_update->checkState() == Qt::Checked)
                main_window_view->m_ui.sort_packages_to_update->click();
        }
    });
}


void MainWindowViewSignals::initSignals()
{
    attachConnectSignalsAfterFillEnd();
    attachMainPreviewsVisibility();

    emit main_window_view->initStarted();
    Logger::logger()->logInfo("Initialization started");

    QObject::connect(main_window_view->updated_packages_column.get(), &UpdatedPackagesColumn::currentPackagesCountChanged, [this](int packages_count){ emit main_window_view->packagesToUpdateCountChanged(packages_count); });

    attachPackagesAccess();
    attachSignalsForSidePreviews();

    QObject::connect(main_window_view->m_ui.check_all_updates_checkbox, &QCheckBox::toggled, main_window_view->updated_packages_column.get(), &UpdatedPackagesColumn::toggleAllPackages);

    if (main_window_view->process.isNull())
        return;

    attachSignalsForProcess();
}


void MainWindowViewSignals::initColumns()
{
    attachAvailablePackagesColumn();
    attachInstalledPackagesColumn();
    attachPackagesToUpdateColumn();
}


void MainWindowViewSignals::attachCheckUpdates()
{
    QtConcurrent::run([&]()
    {
        main_window_view->updated_packages_column->fill();
        emit main_window_view->packagesToUpdateFillEnded();
    });
}
