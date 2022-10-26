#include "process.h"
#include "qmessagebox.h"

#include <QDir>
#include <QSharedPointer>
#include <QProcess>
#include <utility>

Process::Process(Task new_task,
                 QStringList new_checked_packages) :
    task(new_task),
    messages_map(),
    commands_map()
{
    messages_map.insert(Task::Clean, {tr("Clean"), tr("clean packages after installation?")});
    messages_map.insert(Task::MirrorsUpdate, {tr("Update mirrors"), tr("update mirrors?")});
    messages_map.insert(Task::UpdateAll, {tr("Update all"), tr("update all packages?")});
    messages_map.insert(Task::PrintVCSPackages, {tr("Print vcs packages"), tr("print all vcs packages?")});
    messages_map.insert(Task::UpdateInstalledPackages, {tr("Installed packages update"), tr("update installed packages?")});
    messages_map.insert(Task::Uninstall, {tr("Uninstallation"), tr("remove packages?")});
    messages_map.insert(Task::Install, {tr("Installation"), tr("install packages?")});
    messages_map.insert(Task::Update, {tr("Update"), tr("update mirrors?")});

    commands_map.insert(Task::Update, QStringList() << "-t" << "-n" << "-c" << "/bin/bash -c \"pacman -S --noconfirm " + new_checked_packages.join(" ") + "\"");
    commands_map.insert(Task::Clean, QStringList() << "-c" << "pak -Sc");
    commands_map.insert(Task::MirrorsUpdate, QStringList() << "-c" << "pak -m");
    commands_map.insert(Task::UpdateAll, QStringList() << "-c" << "pak -Su");
    commands_map.insert(Task::PrintVCSPackages, QStringList() << "-c" << "pak --vcs");
    commands_map.insert(Task::Uninstall, QStringList() << "-t" << "-n" << "-c" << "/bin/bash -c \"pacman -R --noconfirm " + new_checked_packages.join(" ") + "\"");
    commands_map.insert(Task::Install, QStringList() << "-t" << "-n" << "-c" << "/bin/bash -c \"pacman -S --noconfirm " + new_checked_packages.join(" ") + "\"");
    commands_map.insert(Task::UpdateInstalledPackages, QStringList() << "-c" << "pak -Sy");
}

void Process::run()
{
    int answer = QMessageBox::information(new QWidget, messages_map.value(task).first,
                                          tr("Are you sure you want to %1 ").arg(messages_map.value(task).second),
                                          QMessageBox::Yes | QMessageBox::No);

    if (static_cast<QMessageBox::StandardButton>(answer) == QMessageBox::No)
        return;

    bool containsPacman = commands_map.value(task).join(" ").contains("pacman");
    QSharedPointer<QProcess> pak_s(QSharedPointer<QProcess>(new QProcess));
    pak_s.data()->start(containsPacman ? "/usr/bin/kdesu" : "/bin/bash", commands_map.value(task));
    QObject::connect(pak_s.data(), &QProcess::readyReadStandardOutput, [=]() {
        while (pak_s.data()->canReadLine())
        {
            QString line = pak_s.data()->readLine();
            emit generatedOutput(line);
        }});

    QObject::connect(pak_s.data(), QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred),
        [=](QProcess::ProcessError process_error){  QMessageBox::warning(new QWidget, messages_map.value(task).first, tr("%1 wasn't possible: %2").arg(messages_map.value(task).first).arg(pak_s.data()->error()), QMessageBox::Ok); });
    QObject::connect(pak_s.data(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [=](int exit_code, QProcess::ExitStatus exit_status){ emit finished(exit_code, exit_status); });
}
