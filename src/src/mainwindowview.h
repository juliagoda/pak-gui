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

#pragma once

#include "ui_mainwindowview.h"
#include "ui_packageinput.h"

#include "availablepackagescolumn.h"
#include "installedpackagescolumn.h"
#include "updatedpackagescolumn.h"
#include "progressview.h"
#include "process.h"
#include "actionsaccesschecker.h"
#include "spinninganimation.h"

#include <QStringList>
#include <QSharedPointer>
#include <QWidget>
#include <QPointer>
#include <QThread>
#include <QMap>


namespace Ui {
class MainWindowView;
}

class MainWindowViewSignals;

class MainWindowView : public QWidget
{
    Q_OBJECT

    friend class MainWindowViewSignals;

public:
    enum class State
    {
        Running = 0,
        Waiting
    };

    explicit MainWindowView(QWidget* parent = nullptr);
    ~MainWindowView() override;

    void setProcess(const QWeakPointer<Process>& new_process);
    void setActionsAccessChecker(const QWeakPointer<ActionsAccessChecker>& new_actions_access_checker);
    void init();
    virtual void run();
    void preparePreviews();

public Q_SLOTS:
    void refresh();
    void setForcedUpdateFlag();
    void showInputWidgets(Process::Task task);
    void generatePreview(Process::Task task);
    void showSingleAnimation(Process::Task task);
    void generateOutput(Process::Task task, const QString& line);
    virtual void showStatisticsWindow();
    virtual void downloadPackage();
    virtual void searchPackage();
    void finishProcess(Process::Task task, int exit_code, QProcess::ExitStatus exit_status);
    virtual void checkUpdates();
    virtual void updateWidgets();
    void checkRunningThreadsBeforeQuit();
    bool isRunningMainThreads();
    void blockUpdateColumn();

private Q_SLOTS:
    void startAnimations();
    void connectSignalsForAvailablePackages();
    void connectSignalsForInstalledPackages();
    void connectSignalsForUpdatedPackages();
    void toggleWidgetsAccess(bool is_online);
    void abortProcessFromButton(QProcess* process, QPushButton* button);

signals:
    void operationsAmountIncreased();
    void initStarted();
    void initEnded();
    void availablePackagesFillEnded();
    void installedPackagesFillEnded();
    void packagesToUpdateFillEnded();
    void hideOnlineActions();
    void packagesToUpdateCountChanged(uint packages_count);

protected:
    Ui::MainWindowView m_ui;
    QScopedPointer<AvailablePackagesColumn> available_packages_column{nullptr};
    QScopedPointer<InstalledPackagesColumn> installed_packages_column{nullptr};
    QScopedPointer<UpdatedPackagesColumn> updated_packages_column{nullptr};
    QScopedPointer<SpinningAnimation> spinning_animation{new SpinningAnimation};
    QMap<Process::Task, QPointer<QWidget>> generated_previews_map{};
    QScopedPointer<ProgressView> progress_view{new ProgressView};
    QScopedPointer<MainWindowViewSignals> main_window_view_signals;

    virtual void showFinishInformation();
    virtual void updatePreviewsDesign();

private:
    void addInputWidgets(QVBoxLayout*& vbox_layout,
                         QWidget*& scroll_area_widget_contents,
                         const QString& text);
    void hideWidgets();
    void hideWidgetsExceptInstalled();
    void checkSpinningVisibility();
    void clearMainPreviews(Process::Task task);
    void disconnectSortSignals();
    void reconnectSortSignals();

    QSharedPointer<Process> process{nullptr};
    QSharedPointer<ActionsAccessChecker> actions_access_checker{nullptr};
    QScopedPointer<QTimer> internet_connection_timer{new QTimer};
    State current_state{State::Running};
    QProcess* current_installation_process = nullptr;
    QProcess* current_update_process = nullptr;
    QProcess* current_uninstallation_process = nullptr;
};
