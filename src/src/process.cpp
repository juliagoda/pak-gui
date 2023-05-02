#include "process.h"

#include "outputfilter.h"
#include "actionsaccesschecker.h"
#include "logger.h"
#include "defs.h"

#include <KLocalizedString>
#include <QMessageBox>
#include <QDir>
#include <QSharedPointer>
#include <QProcess>
#include <utility>
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

Process::Process(QSharedPointer<ActionsAccessChecker>& new_actions_access_checker, QWidget* new_parent) :
    messages_map(),
    commands_map(),
    parent(new_parent)
{
    if (!new_actions_access_checker.isNull())
        connect(new_actions_access_checker.get(), &ActionsAccessChecker::auracleAccessChanged, this, &Process::updateCleanCommand);

    messages_map.insert(Task::Clean, {i18n("Clean"), i18n("clean packages after installation?")});
    messages_map.insert(Task::MirrorsUpdate, {i18n("Update mirrors"), i18n("update mirrors?")});
    messages_map.insert(Task::UpdateAll, {i18n("Update all"), i18n("update all packages?")});
    messages_map.insert(Task::PrintVCSPackages, {i18n("Print vcs packages"), i18n("print all vcs packages?")});
    messages_map.insert(Task::UpdateInstalledPackages, {i18n("Installed packages update"), i18n("update installed packages?")});
    messages_map.insert(Task::SyncPOLAUR, {i18n("Sync POLAUR"), i18n("sync POLAUR packages?")});

    commands_map.insert(Task::SyncPOLAUR, QStringList() << "-c" << Constants::askPassCommand() + " && pak -SyP");
    commands_map.insert(Task::Clean, QStringList() << "-c" << Constants::askPassCommand() + " && echo -e \"y\" | pak -Sc");
    commands_map.insert(Task::MirrorsUpdate, QStringList() << "-c" << Constants::askPassCommand() + " && echo -e \"y\" | pak -m");
    commands_map.insert(Task::UpdateAll, QStringList() << "-c" << Constants::askPassCommand() + " && echo -e \"y\ny\" | pak -Su");
    commands_map.insert(Task::PrintVCSPackages, QStringList() << "-c" << Constants::askPassCommand() + " && pak --vcs");
    commands_map.insert(Task::UpdateInstalledPackages, QStringList() << "-c" << Constants::askPassCommand() + " && echo -e \"y\" | pak -Sy");
}


void Process::run(Process::Task new_task,
                  QStringList new_checked_packages)
{
    if (isAlreadyRunning(new_task))
    {
        QMessageBox::warning(parent, messages_map.value(new_task).first,
                             i18n("The task is already running!"),
                             QMessageBox::Ok);

        return;
    }

    updateMap(new_checked_packages);
    if (!askQuestion(new_task, new_checked_packages))
    {
        prepareMapsForNextTask();
        return;
    }

    Logger::logger()->logDebug(QStringLiteral("Packages in current task: %1").arg(new_checked_packages.join(" ")));
    running_tasks_map[new_task] = true;
    emitTask(new_task);
    startProcess(new_task);
    prepareMapsForNextTask();
}


void Process::setPackagesToUpdate(uint packages_to_update_count)
{
    packages_to_update = packages_to_update_count;
}


bool Process::isAlreadyRunning(Task new_task)
{
    if (new_task == Task::Update && running_tasks_map.value(Task::UpdateAll))
        return true;

    if (new_task == Task::UpdateAll && running_tasks_map.value(Task::Update))
        return true;

    return running_tasks_map.value(new_task);
}


void Process::resetRunningTask(Task new_task)
{
    running_tasks_map[new_task] = false;
}


void Process::updateCleanCommand(bool is_auracle_installed)
{
    QString basic_command = Constants::askPassCommand() + " && echo -e \"y\" | pak -Sc";
    commands_map.remove(Task::Clean);

    if (is_auracle_installed)
        commands_map.insert(Task::Clean, QStringList() << "-c" << basic_command + " && echo -e \"y\" | pak -ScA");
    else
        commands_map.insert(Task::Clean, QStringList() << "-c" << basic_command);
}


bool Process::askQuestion(Process::Task new_task,
                          QStringList new_checked_packages)
{
    messages_map.insert(Task::Uninstall, {i18n("Uninstallation"), i18np("remove package?", "remove packages?", new_checked_packages.count())});
    messages_map.insert(Task::Install, {i18n("Installation"), i18np("install package?", "install packages?", new_checked_packages.count())});
    messages_map.insert(Task::InstallAfterSearchRepo, {i18n("Installation from Repo"), i18np("install package?", "install packages?", new_checked_packages.count())});
    messages_map.insert(Task::InstallAfterSearchAUR, {i18n("Installation from AUR"), i18np("install package?", "install packages?", new_checked_packages.count())});
    messages_map.insert(Task::InstallAfterSearchPOLAUR, {i18n("Installation from POLAUR"), i18np("install package?", "install packages?", new_checked_packages.count())});
    messages_map.insert(Task::Update, {i18n("Update"), i18np("update package?", "update packages?", new_checked_packages.count())});

    if (!getAnswer(new_task, new_checked_packages))
        return false;

    if (isNeededAskAboutUpdate(new_task))
        updateCurrentCommandForUpdate(new_task);

    return true;
}


void Process::startProcess(Process::Task new_task)
{
    Logger::logger()->logInfo(QStringLiteral("Started task \"%1\"").arg(QVariant::fromValue(new_task).toString()));
    QSharedPointer<QProcess> pak_s(QSharedPointer<QProcess>(new QProcess));
    pak_s->setProcessChannelMode(QProcess::MergedChannels);
    bool contains_pacman = commands_map.value(new_task).join(" ").contains("pacman");
    connectSignals(pak_s, new_task);
    pak_s.data()->start(contains_pacman ? "/usr/bin/kdesu" : "/bin/bash", commands_map.value(new_task));
    Logger::logger()->writeSectionToFile(Constants::taskToWriteOperationMap().value(new_task));
    QObject::connect(pak_s.data(), &QProcess::readyReadStandardOutput, [pak_s, new_task, this]() {
        while (pak_s.data()->canReadLine())
        {
            QString line = pak_s.data()->readLine();
            processReadLine(line, new_task);
        }});
}


void Process::processReadLine(QString& line, Process::Task new_task)
{
    QString filtered_line = OutputFilter::filteredOutput(line);
    emit generatedOutput(new_task, filtered_line);
    Logger::logger()->writeLineToFile(filtered_line);
}


void Process::connectSignals(QSharedPointer<QProcess>& process, Process::Task new_task)
{
    QObject::connect(process.data(), QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred),
        [this, new_task, process](QProcess::ProcessError process_error)
    {
        QMessageBox::warning(parent, messages_map.value(new_task).first, tr("%1 wasn't possible: %2").arg(messages_map.value(new_task).first).arg(process.data()->error()), QMessageBox::Ok);
        Logger::logger()->logWarning(QStringLiteral("Error occured during task \"%1\" execution: %2").arg(QVariant::fromValue(new_task).toString(), QVariant::fromValue(process_error).toString()));
    });

    QObject::connect(process.data(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [this, new_task](int exit_code, QProcess::ExitStatus exit_status)
    {
        emit finished(new_task, exit_code, exit_status);
        Logger::logger()->logDebug(QStringLiteral("Task \"%1\" finished successfully").arg(QVariant::fromValue(new_task).toString()));
        });
}


bool Process::isNeededAskAboutUpdate(Task new_task)
{
    if (new_task == Task::InstallAfterSearchRepo)
        return true;

    if (new_task == Task::InstallAfterSearchAUR)
        return true;

    if (new_task == Task::InstallAfterSearchPOLAUR)
        return true;

    if (new_task == Task::Install)
        return true;

    return false;
}


bool Process::getAnswer(Task new_task, QStringList new_checked_packages)
{
    int answer = QMessageBox::information(parent, messages_map.value(new_task).first,
        questionForm(new_checked_packages, new_task),
        QMessageBox::Yes | QMessageBox::No);

    if (static_cast<QMessageBox::StandardButton>(answer) == QMessageBox::No)
    {
        Logger::logger()->logDebug(QStringLiteral("Question related to task \"%1\" has been cancelled").arg(QVariant::fromValue(new_task).toString()));
        return false;
    }

    return true;
}


void Process::updateCurrentCommandForUpdate(Task new_task)
{
    auto command = commands_map.value(new_task);

    if (command.count() < 2)
    {
        Logger::logger()->logWarning(QStringLiteral("Command form for current task is incorrect"));
        return;
    }

    if (packages_to_update == 0)
    {
        replaceAutoAcceptationForTask(new_task, "echo -e \"y\"");
        return;
    }

    const bool accepted = getAnswer(Task::UpdateAll, QStringList());

    if (accepted)
    {
        replaceAutoAcceptationForTask(new_task, "echo -e \"y\ny\"");
        return;
    }

    replaceAutoAcceptationForTask(new_task, "echo -e \"n\ny\"");
}


void Process::replaceAutoAcceptationForTask(Task new_task, const QString& acceptation_form)
{
    auto command = commands_map.value(new_task);
    auto last_part = command.at(1);
    last_part = last_part.replace(QRegExp("echo -e \"(n|y)\ny\""), acceptation_form);
    command.pop_back();
    command.push_back(last_part);
    commands_map[new_task] = command;
}


void Process::updateMap(QStringList& checked_packages)
{
    commands_map.insert(Task::Update, QStringList() << "-t" << "-n" << "-c" << "/bin/bash -c \"pacman -Sy --noconfirm " + checked_packages.join(" ") + "\"");
    commands_map.insert(Task::Uninstall, QStringList() << "-c" << Constants::askPassCommand() + " && echo -e \"y\" | pak -R " + checked_packages.join(" "));
    commands_map.insert(Task::Install, QStringList() << "-c" << Constants::askPassCommand() + " && echo -e \"n\ny\" | pak -S " + checked_packages.join(" "));
    commands_map.insert(Task::InstallAfterSearchRepo, QStringList() << "-c" << Constants::askPassCommand() + " && echo -e \"n\ny\" | pak -S " + checked_packages.join(" "));
    commands_map.insert(Task::InstallAfterSearchAUR, QStringList() << "-c" << Constants::askPassCommand() + " && echo -e \"n\ny\" | pak -SA " + checked_packages.join(" "));
    commands_map.insert(Task::InstallAfterSearchPOLAUR, QStringList() << "-c" << Constants::askPassCommand() + " && echo -e \"n\ny\" | pak -SP " + checked_packages.join(" "));
}


void Process::prepareMapsForNextTask()
{
    commands_map.remove(Task::Update);
    commands_map.remove(Task::Uninstall);
    commands_map.remove(Task::Install);
    commands_map.remove(Task::InstallAfterSearchRepo);
    commands_map.remove(Task::InstallAfterSearchAUR);
    commands_map.remove(Task::InstallAfterSearchPOLAUR);

    messages_map.remove(Task::Uninstall);
    messages_map.remove(Task::Install);
    messages_map.remove(Task::Update);
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


QString Process::questionForm(QStringList& new_checked_packages, Task new_task)
{
    QString question = i18n("Are you sure you want to %1", messages_map.value(new_task).second);

    if (new_task != Task::Update && new_checked_packages.count() > 0)
        question.append(":\n\n" + new_checked_packages.join("\n"));

    return question;
}
