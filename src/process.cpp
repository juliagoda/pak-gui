#include "process.h"
#include "outputfilter.h"
#include "logger.h"
#include "defs.h"

#include <KLocalizedString>
#include <QMessageBox>
#include <QDir>
#include <QSharedPointer>
#include <QProcess>
#include <utility>


Process::Process() :
    messages_map(),
    commands_map()
{
    messages_map.insert(Task::Clean, {i18n("Clean"), i18n("clean packages after installation?")});
    messages_map.insert(Task::MirrorsUpdate, {i18n("Update mirrors"), i18n("update mirrors?")});
    messages_map.insert(Task::UpdateAll, {i18n("Update all"), i18n("update all packages?")});
    messages_map.insert(Task::PrintVCSPackages, {i18n("Print vcs packages"), i18n("print all vcs packages?")});
    messages_map.insert(Task::UpdateInstalledPackages, {i18n("Installed packages update"), i18n("update installed packages?")});
    messages_map.insert(Task::Uninstall, {i18n("Uninstallation"), i18n("remove packages?")});
    messages_map.insert(Task::Install, {i18n("Installation"), i18n("install packages?")});
    messages_map.insert(Task::Update, {i18n("Update"), i18n("update package(s)?")});

    commands_map.insert(Task::Clean, QStringList() << "-c" << "y | pak -Sc");
    commands_map.insert(Task::MirrorsUpdate, QStringList() << "-c" << "pak -m");
    commands_map.insert(Task::UpdateAll, QStringList() << "-c" << "pak -Su");
    commands_map.insert(Task::PrintVCSPackages, QStringList() << "-c" << "pak --vcs");
    commands_map.insert(Task::UpdateInstalledPackages, QStringList() << "-c" << "pak -Sy");
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


bool Process::askQuestion(Task new_task,
                          QStringList new_checked_packages)
{
    int answer = QMessageBox::information(new QWidget, messages_map.value(new_task).first,
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
    bool containsPacman = commands_map.value(new_task).join(" ").contains("pacman");
    QSharedPointer<QProcess> pak_s(QSharedPointer<QProcess>(new QProcess));
    pak_s->setProcessChannelMode(QProcess::MergedChannels);
    connectSignals(pak_s, new_task);
    pak_s.data()->start(containsPacman ? "/usr/bin/kdesu" : "/bin/bash", commands_map.value(new_task));
    QString output = QString();
    QObject::connect(pak_s.data(), &QProcess::readyReadStandardOutput, [=, output]() mutable {
        while (pak_s.data()->canReadLine())
        {
            QString line = pak_s.data()->readLine();
            QString filtered_line = OutputFilter::filteredOutput(line);
            emit generatedOutput(new_task, filtered_line);
            output += filtered_line;
        }});

    Logger::logger()->writeToFile(output, task_to_write_operation_map.value(new_task));
}


void Process::connectSignals(QSharedPointer<QProcess>& process, Task new_task)
{
    QObject::connect(process.data(), QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred),
        [=](QProcess::ProcessError process_error)
    {
        QMessageBox::warning(new QWidget, messages_map.value(new_task).first, tr("%1 wasn't possible: %2").arg(messages_map.value(new_task).first).arg(process.data()->error()), QMessageBox::Ok);
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
}


void Process::prepareMapForNextTask()
{
    commands_map.remove(Task::Update);
    commands_map.remove(Task::Uninstall);
    commands_map.remove(Task::Install);
}


void Process::emitSideTask(Task task)
{
    if (task != Task::Install &&
        task != Task::Uninstall &&
        task != Task::Update)
    {
        emit acceptedTask(task);
    }
}


QString Process::questionForm(QStringList& new_checked_packages, Task new_task)
{
    QString question = i18n("Are you sure you want to %1", messages_map.value(new_task).second);

    if (new_checked_packages.count() > 0)
        question.append(":\n\n" + new_checked_packages.join("\n"));

    return question;
}
