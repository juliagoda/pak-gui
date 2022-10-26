#include "packagesmanager.h"

#include <QScopedPointer>
#include <QDir>


PackagesManager::PackagesManager()
{

}


void PackagesManager::update(QStringList checked_packages)
{
    QScopedPointer<Process> process(new Process(Process::Task::Update, checked_packages));
    QObject::connect(process.data(), &Process::generatedOutput, this, [this](const QString& line) { emit generatedUpdateCommandOutput(line); });
    QObject::connect(process.data(), &Process::finished, this, [this](int exit_code, QProcess::ExitStatus exit_status) { emit finishedUpdate(exit_code, exit_status); });
    process->run();
}


void PackagesManager::install(QStringList checked_packages)
{
    QScopedPointer<Process> process(new Process(Process::Task::Install, checked_packages));
    QObject::connect(process.data(), &Process::generatedOutput, this, [this](const QString& line) { emit generatedInstallCommandOutput(line); });
    QObject::connect(process.data(), &Process::finished, this, [this](int exit_code, QProcess::ExitStatus exit_status) { emit finishedInstall(exit_code, exit_status); });
    process->run();
}


void PackagesManager::uninstall(QStringList checked_packages)
{
    QScopedPointer<Process> process(new Process(Process::Task::Uninstall, checked_packages));
    QObject::connect(process.data(), &Process::generatedOutput, this, [this](const QString& line) { emit generatedUninstallCommandOutput(line); });
    QObject::connect(process.data(), &Process::finished, this, [this](int exit_code, QProcess::ExitStatus exit_status) { emit finishedUninstall(exit_code, exit_status); });
    process->run();
}


void PackagesManager::clean()
{
    QScopedPointer<Process> process(new Process(Process::Task::Clean));
    QObject::connect(process.data(), &Process::generatedOutput, this, [this](const QString& line) { emit generatedCleanCommandOutput(line); });
    QObject::connect(process.data(), &Process::finished, this, [this](int exit_code, QProcess::ExitStatus exit_status) { emit finishedClean(exit_code, exit_status); });
    process->run();

    emit acceptedTask(Process::Task::Clean);
}


void PackagesManager::updateMirrors()
{
    QScopedPointer<Process> process(new Process(Process::Task::MirrorsUpdate));
    QObject::connect(process.data(), &Process::generatedOutput, this, [this](const QString& line) { emit generatedMirrorsUpdateCommandOutput(line); });
    QObject::connect(process.data(), &Process::finished, this, [this](int exit_code, QProcess::ExitStatus exit_status) { emit finishedMirrorsUpdate(exit_code, exit_status); });
    process->run();

    emit acceptedTask(Process::Task::MirrorsUpdate);
}


void PackagesManager::updateAll()
{
    QScopedPointer<Process> process(new Process(Process::Task::UpdateAll));
    QObject::connect(process.data(), &Process::generatedOutput, this, [this](const QString& line) { emit generatedUpdateAllCommandOutput(line); });
    QObject::connect(process.data(), &Process::finished, this, [this](int exit_code, QProcess::ExitStatus exit_status) { emit finishedUpdateAll(exit_code, exit_status); });
    process->run();

    emit acceptedTask(Process::Task::UpdateAll);
}


void PackagesManager::printInstalledVCSPackages()
{
    QScopedPointer<Process> process(new Process(Process::Task::PrintVCSPackages));
    QObject::connect(process.data(), &Process::generatedOutput, this, [this](const QString& line) { emit generatedPrintVCSPackagesCommandOutput(line); });
    QObject::connect(process.data(), &Process::finished, this, [this](int exit_code, QProcess::ExitStatus exit_status) { emit finishedVCSPackagesPrint(exit_code, exit_status); });
    process->run();

    emit acceptedTask(Process::Task::PrintVCSPackages);
}


void PackagesManager::updateInstalledPackages()
{
    QScopedPointer<Process> process(new Process(Process::Task::UpdateInstalledPackages));
    QObject::connect(process.data(), &Process::generatedOutput, this, [this](const QString& line) { emit generatedInstalledPackagesUpdateCommandOutput(line); });
    QObject::connect(process.data(), &Process::finished, this, [this](int exit_code, QProcess::ExitStatus exit_status) { emit finishedInstalledPackagesUpdate(exit_code, exit_status); });
    process->run();

    emit acceptedTask(Process::Task::UpdateInstalledPackages);
}
