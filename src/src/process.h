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

#include <QObject>
#include <QProcess>
#include <QString>
#include <QMap>
#include <QStringList>
#include <QSharedPointer>

#include <mutex>


class ActionsAccessChecker;

class Process : public QObject
{
    Q_OBJECT

public:
    enum class Task
    {
        Unknown,
        Clean,
        MirrorsUpdate,
        UpdateAll,
        PrintVCSPackages,
        UpdateInstalledPackages,
        Uninstall,
        Install,
        InstallAfterSearchRepo,
        InstallAfterSearchAUR,
        InstallAfterSearchPOLAUR,
        Update,
        SyncPOLAUR
    };
    Q_ENUM(Task)

    explicit Process(const QSharedPointer<ActionsAccessChecker>& new_actions_access_checker, QWidget* new_parent);
    ~Process() override = default;

    bool preparedBeforeRun(Process::Task new_task, QStringList new_checked_packages = QStringList());
    void run(Process::Task new_task, QStringList new_checked_packages = QStringList());
    void setPackagesToUpdate(uint packages_to_update_count);
    void setAurPackagesToUpdate(uint packages_to_update_count);
    void stop();
    static bool isAlreadyRunning(Process::Task new_task);
    static void resetRunningTask(Process::Task new_task);

protected:
    virtual void startProcess(Task new_task);
    virtual bool askQuestion(Task new_task, const QStringList& new_checked_packages);
    void processReadLine(const QString& line, Process::Task new_task);

private Q_SLOTS:
    void updateCleanCommand(bool is_auracle_installed);

public Q_SLOTS:
    void inputAnswer(const QString& new_answer, Process::Task task);

signals:
    void finished(Process::Task task, int exit_code, QProcess::ExitStatus exit_status);
    void generatedOutput(Process::Task task, const QString& line);
    void acceptedTask(Process::Task task);
    void acceptedMainTask(Process::Task task);
    void showInput(Process::Task task);
    void acceptedUpdateAll();
    void ended();

private:
    void setDefaultCommands();
    void updateMaps(QStringList& checked_packages);
    void prepareMapsForNextTask();
    void emitTask(Process::Task task);
    QString questionForm(const QStringList& new_checked_packages, Task new_task);
    void connectSignals(Task new_task);
    void connectReadyReadStandardOutput(Task new_task);
    bool isNeededAskAboutUpdate(Task new_task);
    bool getAnswer(Process::Task new_task, const QStringList& new_checked_packages);
    void updateCurrentCommandForUpdate(Process::Task new_task);
    void replaceAutoAcceptationForTask(Process::Task new_task, const QString& original_form, const QString& acceptation_form);
    void removeAutoAcceptationFromCommand(Process::Task new_task);
    void changeUpdateAllCommand(Process::Task new_task);
    static bool isUpdateTask(Process::Task new_task);
    static bool isRunningUpdateTask();
    static void updateYesNoCommands();

    static QString yes_command;
    static QString no_command;
    QMap<Task, QPair<QString, QString>> messages_map;
    QMap<Task, QStringList> commands_map;
    QMap<Task, QSharedPointer<QProcess>> process_map;
    QSharedPointer<QProcess> current_process;
    uint packages_to_update = 0;
    uint aur_packages_to_update_count = 0;
    QWidget* parent;
    std::once_flag yes_no_commands_update;
};

