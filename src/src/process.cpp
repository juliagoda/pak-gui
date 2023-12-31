// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of  package manager based on "pak" application.
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

#include "process.h"

#include "src/settingsrecords.h"
#include "src/actionsaccesschecker.h"
#include "src/logger.h"
#include "src/defs.h"
#include "src/outputfilter.h"
#include "src/settings.h"
#include "src/outputfilter.h"
#include "src/messagebox.h"

#include <KLocalizedString>
#include <QMessageBox>
#include <QDir>
#include <QSharedPointer>
#include <QProcess>
#include <utility>
#include <QSharedPointer>
#include <QDebug>


QMap<Process::Task, bool> running_tasks_map{
                                            {Process::Task::Clean, false},
                                            {Process::Task::MirrorsUpdate, false},
                                            {Process::Task::UpdateAll, false},
                                            {Process::Task::PrintVCSPackages, false},
                                            {Process::Task::UpdateInstalledPackages, false},
                                            {Process::Task::Uninstall, false},
                                            {Process::Task::Install, false},
                                            {Process::Task::InstallAfterSearchRepo, false},
                                            {Process::Task::InstallAfterSearchAUR, false},
                                            {Process::Task::InstallAfterSearchPOLAUR, false},
                                            {Process::Task::Update, false},
                                            {Process::Task::SyncPOLAUR, false},
                                            };

QString Process::yes_command = "Y";
QString Process::no_command = "n";


Process::Process(const QSharedPointer<ActionsAccessChecker>& new_actions_access_checker, QWidget* new_parent) :
    messages_map(),
    commands_map(),
    process_map(),
    current_process{nullptr},
    parent(new_parent)
{
    std::call_once(yes_no_commands_update, updateYesNoCommands);

    if (!new_actions_access_checker.isNull())
        connect(new_actions_access_checker.get(), &ActionsAccessChecker::auracleAccessChanged, this, &Process::updateCleanCommand);

    // TODOJG - lazy evaluation / strategy design instead of map
    messages_map.insert(Task::Clean, {i18n("Clean"), i18n("clean packages after installation?")});
    messages_map.insert(Task::MirrorsUpdate, {i18n("Update mirrors"), i18n("update mirrors?")});
    messages_map.insert(Task::UpdateAll, {i18n("Update all"), i18n("update all system packages packages?")});
    messages_map.insert(Task::PrintVCSPackages, {i18n("Print vcs packages"), i18n("print all vcs packages?")});
    messages_map.insert(Task::UpdateInstalledPackages, {i18n("Installed packages update"), i18n("update installed packages?")});
    messages_map.insert(Task::SyncPOLAUR, {i18n("Sync POLAUR"), i18n("sync POLAUR packages?")});

    setDefaultCommands();
}


bool Process::preparedBeforeRun(Task new_task, QStringList new_checked_packages)
{
    if (isAlreadyRunning(new_task))
    {
        QMessageBox::warning(parent, messages_map.value(new_task).first,
                             i18n("The task is already running!"),
                             QMessageBox::Ok);

        return false;
    }

    updateMaps(new_checked_packages);

    if (!askQuestion(new_task, new_checked_packages))
    {
        prepareMapsForNextTask();
        return false;
    }

    if (isTaskAlwaysManual(new_task))
    {
        QMessageBox::information(parent, messages_map.value(new_task).first,
        i18n("Respond to questions manually below the preview"),
        QMessageBox::Ok);
    }

    return true;
}


void Process::setDefaultCommands()
{
    // TODOJG - lazy evaluation / strategy design instead of map
    Constants constants;
    commands_map[Task::SyncPOLAUR] = QStringList() << "-c" << constants.askPassCommand() + " && pak -SyP";
    commands_map[Task::Clean] = QStringList() << "-c" << constants.askPassCommand() + " && echo -e \"" + yes_command + "\" | pak -Sc";
    commands_map[Task::MirrorsUpdate] = QStringList() << "-c" << constants.askPassCommand() + " && echo -e \"" + yes_command + "\" | pak -m";
    commands_map[Task::UpdateAll] = QStringList() << "-c" << constants.askPassCommand() + " && echo -e \"" + yes_command + "\n" + yes_command + "\" | pak -Su";
    commands_map[Task::PrintVCSPackages] = QStringList() << "-c" << constants.askPassCommand() + " && pak --vcs";
    commands_map[Task::UpdateInstalledPackages] = QStringList() << "-c" << constants.askPassCommand() + " && echo -e \"" + yes_command + "\" | pak -Sy";
}


void Process::run(Process::Task new_task,
                  QStringList new_checked_packages)
{
    Logger::logger()->logDebug(QStringLiteral("Packages in current task: %1").arg(new_checked_packages.join(" ")));
    running_tasks_map[new_task] = true;
    if (Settings::records()->operateOnActionsManually())
    {
        removeAutoAcceptationFromCommand(new_task);
        emit showInput(new_task);
    }

    changeUpdateAllCommand(new_task);
    startProcess(new_task);
    prepareMapsForNextTask();
}


void Process::inputAnswer(const QString& new_answer, Process::Task task)
{
    if (new_answer.isEmpty())
    {
        Logger::logger()->logWarning("Answer is empty string");
        return;
    }

    if (process_map.value(task, nullptr).isNull())
    {
        Logger::logger()->logWarning("Current process is empty");
        return;
    }

    if (process_map.value(task)->state() != QProcess::Running && !process_map.value(task)->isWritable())
    {
        Logger::logger()->logWarning("Process is not running or is not writable. Answer input is not possible");
        return;
    }

    Logger::logger()->logInfo(QStringLiteral("Input: %1").arg(new_answer));
    process_map.value(task)->write(new_answer.toLocal8Bit() + "\n");
    process_map.value(task)->waitForReadyRead();
}


void Process::setFirstUpdateInitializationFlag()
{
    was_update_initialized = true;
}


void Process::setPackagesToUpdate(uint packages_to_update_count)
{
    packages_to_update = packages_to_update_count;
}


void Process::setAurPackagesToUpdate(uint packages_to_update_count)
{
    aur_packages_to_update_count = packages_to_update_count;
}


void Process::stop()
{
    if (current_process.isNull())
    {
        Logger::logger()->logInfo("Current process cannot be stopped. Process is null.");
        return;
    }

    current_process->terminate();
}


bool Process::isAlreadyRunning(Task new_task)
{
    if (isUpdateTask(new_task) && isRunningUpdateTask())
        return true;

    return running_tasks_map.value(new_task);
}


void Process::resetRunningTask(Task new_task)
{
    running_tasks_map[new_task] = false;
}


QProcess* Process::getCurrentProcess() const
{
    return current_process.get();
}


bool Process::isTaskAlwaysManual(Task new_task)
{
    return new_task == Task::InstallAfterSearchRepo ||
           new_task == Task::InstallAfterSearchAUR ||
           new_task == Task::InstallAfterSearchPOLAUR;
}


void Process::updateCleanCommand(bool is_auracle_installed)
{
    Constants constants;
    QString basic_command = constants.askPassCommand() + " && echo -e \"" + yes_command + "\" | pak -Sc";
    commands_map.remove(Task::Clean);

    if (is_auracle_installed)
        commands_map.insert(Task::Clean, QStringList() << "-c" << basic_command + " && echo -e \"" + yes_command + "\" | pak -ScA");

    if (!is_auracle_installed)
        commands_map.insert(Task::Clean, QStringList() << "-c" << basic_command);
}


bool Process::askQuestion(Process::Task new_task,
                          const QStringList& new_checked_packages)
{
    if (!getAnswer(new_task, new_checked_packages))
        return false;

    if (isNeededAskAboutUpdate(new_task))
        updateCurrentCommandForUpdate(new_task);

    return true;
}


void Process::startProcess(Process::Task new_task)
{
    Logger::logger()->logInfo(QStringLiteral("Started task \"%1\"").arg(QVariant::fromValue(new_task).toString()));

    current_process.reset(new QProcess);

    isUpdateTask(new_task) ? process_map[Task::Update] = current_process.toWeakRef() : process_map[new_task] = current_process.toWeakRef();
    emitTask(new_task);
    current_process->setProcessChannelMode(QProcess::MergedChannels);
    bool contains_pacman = commands_map.value(new_task).join(" ").contains("pacman");
    connectSignals(new_task);
    connectReadyReadStandardOutput(new_task);

    current_process.data()->start(contains_pacman ? "/usr/bin/kdesu" : "/bin/bash", commands_map.value(new_task));
    current_process.data()->waitForStarted();

    Constants constants;
    Logger::logger()->writeSectionToFile(constants.taskToWriteOperation(new_task));
}


void Process::processReadLine(const QString& line, Process::Task new_task)
{
    QScopedPointer<OutputFilter> output_filter{new OutputFilter};
    QString filtered_line = output_filter->filteredOutput(line);
    emit generatedOutput(new_task, filtered_line);

    Logger::logger()->writeLineToFile(filtered_line);
}


void Process::connectSignals(Process::Task new_task)
{
    if (current_process.isNull())
        return;

    QObject::connect(this, &Process::ended, this, [this]()
    {
        if (current_process.isNull())
            return;

        current_process->closeReadChannel(QProcess::StandardOutput);
        current_process->closeReadChannel(QProcess::StandardError);
        current_process->closeWriteChannel();
        current_process->close();
        current_process->kill();
        aur_packages_to_update_count = 0;
        packages_to_update = 0;
    });

    QObject::connect(current_process.data(), QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred),
        [this, new_task](QProcess::ProcessError process_error)
        {
            MessageBox message_box(QMessageBox::Warning, QMessageBox::Ok);
            message_box.setParent(parent);
            message_box.setTitle(messages_map.value(new_task).first);
            QString form = "%1 " + i18n("wasn't possible:") + " %2";
            message_box.setText(form.arg(messages_map.value(new_task).first).arg(QVariant::fromValue(process_error).toString()));
            message_box.run();
            Logger::logger()->writeLineToFile(QString("\n\n\n---------------[END]---------------"));
            Logger::logger()->logWarning(QStringLiteral("Error occured during task \"%1\" execution: %2").arg(QVariant::fromValue(new_task).toString(), QVariant::fromValue(process_error).toString()));
            aur_packages_to_update_count = 0;
            packages_to_update = 0;
        });

    QObject::connect(current_process.data(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [this, new_task](int exit_code, QProcess::ExitStatus exit_status)
        {
            Logger::logger()->writeLineToFile(QString("\n\n\n---------------[END]---------------"));
            emit finished(new_task, exit_code, exit_status);
            Logger::logger()->logDebug(QStringLiteral("Task \"%1\" finished successfully").arg(QVariant::fromValue(new_task).toString()));
            emit ended();
            aur_packages_to_update_count = 0;
            packages_to_update = 0;
        });
}


void Process::connectReadyReadStandardOutput(Task new_task)
{
    if (current_process.isNull())
        return;

    QObject::connect(current_process.data(), &QProcess::readyReadStandardOutput, [new_task, this]()
    {
        if (Settings::records()->operateOnActionsManually() || aur_packages_to_update_count > 0|| isTaskAlwaysManual(new_task))
        {
            QString result{current_process->readAllStandardOutput()};
            processReadLine(result, new_task);
        }

        while (current_process.data()->canReadLine())
        {
            QString line = current_process.data()->readLine();
            processReadLine(line, new_task);
        }
    });
}


bool Process::isNeededAskAboutUpdate(Task new_task)
{
    if (Settings::records()->operateOnActionsManually())
        return false;

    if (new_task == Task::Install && was_update_initialized)
        return true;

    return false;
}


bool Process::getAnswer(Task new_task, const QStringList& new_checked_packages)
{
    MessageBox message_box(QMessageBox::Information, QMessageBox::Yes | QMessageBox::No);
    message_box.setParent(parent);
    message_box.setTitle(messages_map.value(new_task).first);
    message_box.setText(questionForm(new_checked_packages, new_task));
    int answer = message_box.run();

    if (static_cast<QMessageBox::StandardButton>(answer) == QMessageBox::No)
    {
        Logger::logger()->logDebug(QStringLiteral("Question related to task \"%1\" has been cancelled").arg(QVariant::fromValue(new_task).toString()));
        return false;
    }

    return true;
}


void Process::updateCurrentCommandForUpdate(Task new_task)
{
    const auto& command = commands_map.value(new_task);

    if (command.count() < 2)
    {
        Logger::logger()->logWarning(QStringLiteral("Command form for current task is incorrect"));
        return;
    }

    if (packages_to_update == 0)
    {
        replaceAutoAcceptationForTask(new_task, "echo -e \"(" + no_command + "|" + yes_command + ")\n" + yes_command + "\"", "echo -e \"" + yes_command + "\"");
        return;
    }

    const bool accepted = getAnswer(Task::UpdateAll, QStringList());

    if (accepted)
    {
        emit acceptedUpdateAll();
        replaceAutoAcceptationForTask(new_task, "echo -e \"(" + no_command + "|" + yes_command + ")\n" + yes_command + "\"", "echo -e \"" + yes_command + "\n" + yes_command + "\"");
        return;
    }

    replaceAutoAcceptationForTask(new_task, "echo -e \"(" + no_command + "|" + yes_command + ")\n" + yes_command + "\"", "echo -e \"" + no_command + "\n" + yes_command + "\"");
}


void Process::replaceAutoAcceptationForTask(Task new_task,
                                            const QString& original_form,
                                            const QString& acceptation_form)
{
    auto command = commands_map.value(new_task);
    auto last_part = command.at(1);
    last_part = last_part.replace(QRegExp(original_form), acceptation_form);
    command.pop_back();
    command.push_back(last_part);
    commands_map[new_task] = command;
}


void Process::removeAutoAcceptationFromCommand(Process::Task new_task)
{
    auto command = commands_map.value(new_task);
    auto last_part = command.at(1);
    last_part = last_part.remove(QRegExp("echo.*\\|\\s+"));
    command.pop_back();
    command.push_back(last_part);
    commands_map[new_task] = command;
}


void Process::changeUpdateAllCommand(Task new_task)
{
    const bool is_command_change_not_needed = aur_packages_to_update_count == 0;
    if (is_command_change_not_needed)
        return;

    QMessageBox::information(parent, messages_map.value(new_task).first,
                             i18n("Select preview and respond to questions manually"),
                             QMessageBox::Ok);

    auto command = commands_map.value(new_task);

    if (command.count() < 2)
    {
        Logger::logger()->logWarning(QStringLiteral("Command form for current task is incorrect"));
        return;
    }

    emit showInput(new_task);

    removeAutoAcceptationFromCommand(new_task);
}


bool Process::isUpdateTask(Task new_task)
{
    return new_task == Process::Task::Update ||
           new_task == Process::Task::UpdateAll ||
           new_task == Process::Task::UpdateInstalledPackages;
}


bool Process::isRunningUpdateTask()
{
    return running_tasks_map.value(Task::UpdateAll) ||
           running_tasks_map.value(Task::Update) ||
           running_tasks_map.value(Task::UpdateInstalledPackages);
}


void Process::updateYesNoCommands()
{
    Constants constants;
    auto yesNoCommand = constants.langNamesToYesNo(QLocale::system().language());
    yes_command = yesNoCommand.first;
    no_command = yesNoCommand.second;
}


void Process::updateMaps(QStringList& checked_packages)
{
    // TODOJG - lazy evaluation / strategy design instead of map
    Constants constants;
    commands_map.insert(Task::Update, QStringList() << "-t" << "-n" << "-c" << "/bin/bash -c \"pacman -Sy --noconfirm " + checked_packages.join(" ") + "\"");
    commands_map.insert(Task::Uninstall, QStringList() << "-c" << constants.askPassCommand() + " && echo -e \"" + yes_command + "\" | pak -Rs " + checked_packages.join(" "));
    commands_map.insert(Task::Install, QStringList() << "-c" << constants.askPassCommand() + " && echo -e \"" + no_command + "\n" + yes_command + "\" | pak -S " + checked_packages.join(" "));
    commands_map.insert(Task::InstallAfterSearchRepo, QStringList() << "-c" << constants.askPassCommand() + " && pak -S " + checked_packages.join(" "));
    commands_map.insert(Task::InstallAfterSearchAUR, QStringList() << "-c" << constants.askPassCommand() + " && pak -SA " + checked_packages.join(" "));
    commands_map.insert(Task::InstallAfterSearchPOLAUR, QStringList() << "-c" << constants.askPassCommand() + " && pak -SP " + checked_packages.join(" "));

    messages_map.insert(Task::Uninstall, {i18n("Uninstallation"), i18np("remove package?", "remove packages?", checked_packages.count())});
    messages_map.insert(Task::Install, {i18n("Installation"), i18np("install package?", "install packages?", checked_packages.count())});
    messages_map.insert(Task::InstallAfterSearchRepo, {i18n("Installation from Repo"), i18np("install package?", "install packages?", checked_packages.count())});
    messages_map.insert(Task::InstallAfterSearchAUR, {i18n("Installation from AUR"), i18np("install package?", "install packages?", checked_packages.count())});
    messages_map.insert(Task::InstallAfterSearchPOLAUR, {i18n("Installation from POLAUR"), i18np("install package?", "install packages?", checked_packages.count())});
    messages_map.insert(Task::Update, {i18n("Update"), i18np("update package?", "update packages?", checked_packages.count())});
}


void Process::prepareMapsForNextTask()
{
    // TODOJG - lazy evaluation / strategy design instead of map
    commands_map.remove(Task::Update);
    commands_map.remove(Task::Uninstall);
    commands_map.remove(Task::Install);
    commands_map.remove(Task::InstallAfterSearchRepo);
    commands_map.remove(Task::InstallAfterSearchAUR);
    commands_map.remove(Task::InstallAfterSearchPOLAUR);

    messages_map.remove(Task::Uninstall);
    messages_map.remove(Task::Install);
    messages_map.remove(Task::Update);

    setDefaultCommands();
}


void Process::emitTask(Task task)
{
    if (task != Task::Install &&
        task != Task::Uninstall &&
        task != Task::Update &&
        task != Task::UpdateAll)
    {
        emit acceptedTask(task);
        return;
    }

    emit acceptedMainTask(task);
}


QString Process::questionForm(const QStringList& new_checked_packages, Task new_task)
{
    QString question = i18n("Are you sure you want to %1", messages_map.value(new_task).second);

    if (new_task != Task::Update && new_checked_packages.count() > 0)
        question.append(":\n\n" + new_checked_packages.join("\n"));

    return question;
}
