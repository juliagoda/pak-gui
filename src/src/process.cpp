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


Process::Process(QSharedPointer<ActionsAccessChecker>& new_actions_access_checker, QWidget* new_parent) :
    messages_map(),
    commands_map(),
    parent(new_parent)
{
    connect(new_actions_access_checker.get(), &ActionsAccessChecker::auracleAccessChanged, this, &Process::updateCleanCommand);

    messages_map.insert(Task::Clean, {i18n("Clean"), i18n("clean packages after installation?")});
    messages_map.insert(Task::MirrorsUpdate, {i18n("Update mirrors"), i18n("update mirrors?")});
    messages_map.insert(Task::UpdateAll, {i18n("Update all"), i18n("update all packages?")});
    messages_map.insert(Task::PrintVCSPackages, {i18n("Print vcs packages"), i18n("print all vcs packages?")});
    messages_map.insert(Task::UpdateInstalledPackages, {i18n("Installed packages update"), i18n("update installed packages?")});
    messages_map.insert(Task::Uninstall, {i18n("Uninstallation"), i18n("remove packages?")});
    messages_map.insert(Task::Install, {i18n("Installation"), i18n("install packages?")});
    messages_map.insert(Task::Update, {i18n("Update"), i18n("update package(s)?")});

    commands_map.insert(Task::Clean, QStringList() << "-c" << ASKPASS_COMMAND + " && echo -e \"y\" | pak -Sc");
    commands_map.insert(Task::MirrorsUpdate, QStringList() << "-c" << ASKPASS_COMMAND + " && pak -m");
    commands_map.insert(Task::UpdateAll, QStringList() << "-c" << ASKPASS_COMMAND + " && echo -e \"y\ny\" | pak -Su");
    commands_map.insert(Task::PrintVCSPackages, QStringList() << "-c" << ASKPASS_COMMAND + " && pak --vcs");
    commands_map.insert(Task::UpdateInstalledPackages, QStringList() << "-c" << ASKPASS_COMMAND + " && pak -Sy");
}


void Process::run(Task new_task,
                  QStringList new_checked_packages)
{
    if (!askQuestion(new_task, new_checked_packages))
        return;

    Logger::logger()->logDebug(QStringLiteral("Packages in current task: %1").arg(new_checked_packages.join(" ")));
    updateMap(new_checked_packages);
    emitSideTask(new_task);
    startProcess(new_task);
    prepareMapForNextTask();
}


void Process::updateCleanCommand(bool is_auracle_installed)
{
    QString basic_command = ASKPASS_COMMAND + " && echo -e \"y\" | pak -Sc";
    commands_map.remove(Task::Clean);

    if (is_auracle_installed)
        commands_map.insert(Task::Clean, QStringList() << "-c" << basic_command + " && echo -e \"y\" | pak -ScA");
    else
        commands_map.insert(Task::Clean, QStringList() << "-c" << basic_command);
}


bool Process::askQuestion(Task new_task,
                          QStringList new_checked_packages)
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


void Process::startProcess(Task new_task)
{
    Logger::logger()->logInfo(QStringLiteral("Started task \"%1\"").arg(QVariant::fromValue(new_task).toString()));
    QSharedPointer<QProcess> pak_s(QSharedPointer<QProcess>(new QProcess));
    pak_s->setProcessChannelMode(QProcess::MergedChannels);
    bool contains_pacman = commands_map.value(new_task).join(" ").contains("pacman");
    connectSignals(pak_s, new_task);
    pak_s.data()->start(contains_pacman ? "/usr/bin/kdesu" : "/bin/bash", commands_map.value(new_task));
    Logger::logger()->writeSectionToFile(task_to_write_operation_map.value(new_task));
    QObject::connect(pak_s.data(), &QProcess::readyReadStandardOutput, [=]() {
        while (pak_s.data()->canReadLine())
        {
            QString line = pak_s.data()->readLine();
            QString filtered_line = OutputFilter::filteredOutput(line);
            emit generatedOutput(new_task, filtered_line);
            Logger::logger()->writeLineToFile(filtered_line);
        }});
}


void Process::connectSignals(QSharedPointer<QProcess>& process, Task new_task)
{
    QObject::connect(process.data(), QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred),
        [=](QProcess::ProcessError process_error)
    {
        QMessageBox::warning(parent, messages_map.value(new_task).first, tr("%1 wasn't possible: %2").arg(messages_map.value(new_task).first).arg(process.data()->error()), QMessageBox::Ok);
        Logger::logger()->logWarning(QStringLiteral("Error occured during task \"%1\" execution: %2").arg(QVariant::fromValue(new_task).toString()).arg(QVariant::fromValue(process_error).toString()));
    });

    QObject::connect(process.data(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [=](int exit_code, QProcess::ExitStatus exit_status)
    {
        emit finished(new_task, exit_code, exit_status);
        Logger::logger()->logDebug(QStringLiteral("Task \"%1\" finished successfully").arg(QVariant::fromValue(new_task).toString()));
    });
}


void Process::updateMap(QStringList& checked_packages)
{
    commands_map.insert(Task::Update, QStringList() << "-t" << "-n" << "-c" << "/bin/bash -c \"pacman -Sy --noconfirm " + checked_packages.join(" ") + "\"");
    commands_map.insert(Task::Uninstall, QStringList() << "-t" << "-n" << "-c" << "/bin/bash -c \"pacman -R --noconfirm " + checked_packages.join(" ") + "\"");
    commands_map.insert(Task::Install, QStringList() << "-t" << "-n" << "-c" << "/bin/bash -c \"pacman -S --noconfirm " + checked_packages.join(" ") + "\"");
    commands_map.insert(Task::InstallAfterSearchRepo, QStringList() << "-c" << ASKPASS_COMMAND + " && pak -S " + checked_packages.join(" "));
    commands_map.insert(Task::InstallAfterSearchAUR, QStringList() << "-c" << ASKPASS_COMMAND + " && pak -SA " + checked_packages.join(" "));
    commands_map.insert(Task::InstallAfterSearchPOLAUR, QStringList() << "-c" << ASKPASS_COMMAND + " && pak -SP " + checked_packages.join(" "));
}


void Process::prepareMapForNextTask()
{
    commands_map.remove(Task::Update);
    commands_map.remove(Task::Uninstall);
    commands_map.remove(Task::Install);
    commands_map.remove(Task::InstallAfterSearchRepo);
    commands_map.remove(Task::InstallAfterSearchAUR);
    commands_map.remove(Task::InstallAfterSearchPOLAUR);
}


void Process::emitSideTask(Task task)
{
    if (task != Task::Install &&
        task != Task::Uninstall &&
        task != Task::Update &&
        task != Task::UpdateAll)
    {
        emit acceptedTask(task);
    }
}


QString Process::questionForm(QStringList& new_checked_packages, Task new_task)
{
    QString question = i18n("Are you sure you want to %1", messages_map.value(new_task).second);

    if (new_task != Task::Update && new_checked_packages.count() > 0)
        question.append(":\n\n" + new_checked_packages.join("\n"));

    return question;
}