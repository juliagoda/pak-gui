#include "packagesmanager.h"
#include "qmessagebox.h"

#include <QDir>
#include <QSharedPointer>


PackagesManager::PackagesManager()
{

}


void PackagesManager::update(QStringList checked_packages)
{
    int answer = QMessageBox::information(new QWidget, tr("Update"),
                                          tr("Are you sure you want to update packages?"),
                                          QMessageBox::Yes | QMessageBox::No);

    if (static_cast<QMessageBox::StandardButton>(answer) == QMessageBox::No)
        return;

    QSharedPointer<QProcess> pak_s(QSharedPointer<QProcess>(new QProcess));
    pak_s.data()->start("/usr/bin/kdesu", QStringList() << "-t" << "-n" << "-c" << "/bin/bash -c \"pacman -S --noconfirm " + checked_packages.join(" ") + "\"");
    QObject::connect(pak_s.data(), &QProcess::readyReadStandardOutput, [=]() {
        while (pak_s.data()->canReadLine())
        {
            QString line = pak_s.data()->readLine();
            emit generatedUpdateCommandOutput(line);
        }});

    QObject::connect(pak_s.data(), QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred),
        [=](QProcess::ProcessError process_error){  QMessageBox::warning(new QWidget, tr("Update"), tr("Packages couln't be updated: %1").arg(pak_s.data()->error()), QMessageBox::Ok); });
    QObject::connect(pak_s.data(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [=](int exit_code, QProcess::ExitStatus exit_status){ emit finishedUpdate(exit_code, exit_status); });
}


void PackagesManager::install(QStringList checked_packages)
{
    int answer = QMessageBox::information(new QWidget, tr("Installation"),
                                          tr("Are you sure you want to install packages?"),
                                          QMessageBox::Yes | QMessageBox::No);

    if (static_cast<QMessageBox::StandardButton>(answer) == QMessageBox::No)
        return;

    QSharedPointer<QProcess> pak_s(QSharedPointer<QProcess>(new QProcess));
    pak_s.data()->start("/usr/bin/kdesu", QStringList() << "-t" << "-n" << "-c" << "/bin/bash -c \"pacman -S --noconfirm " + checked_packages.join(" ") + "\"");
    QObject::connect(pak_s.data(), &QProcess::readyReadStandardOutput, [=]() {
        while (pak_s.data()->canReadLine())
        {
            QString line = pak_s.data()->readLine();
            emit generatedInstallCommandOutput(line);
        }});

    QObject::connect(pak_s.data(), QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred),
        [=](QProcess::ProcessError process_error){  QMessageBox::warning(new QWidget, tr("Installation"), tr("Packages couln't be installed: %1").arg(pak_s.data()->error()), QMessageBox::Ok); });
    QObject::connect(pak_s.data(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [=](int exit_code, QProcess::ExitStatus exit_status){
        emit finishedInstall(exit_code, exit_status); });
}


void PackagesManager::uninstall(QStringList checked_packages)
{
    int answer = QMessageBox::information(new QWidget, tr("Uninstallation"),
                                          tr("Are you sure you want to uninstall packages?"),
                                          QMessageBox::Yes | QMessageBox::No);

    if (static_cast<QMessageBox::StandardButton>(answer) == QMessageBox::No)
        return;

    QSharedPointer<QProcess> pak_r(QSharedPointer<QProcess>(new QProcess));
    pak_r.data()->start("/usr/bin/kdesu", QStringList() << "-t" << "-n" << "-c" << "/bin/bash -c \"pacman -R --noconfirm " + checked_packages.join(" ") + "\"");
    QObject::connect(pak_r.data(), &QProcess::readyReadStandardOutput, [=]() {
        while (pak_r.data()->canReadLine())
        {
            QString line = pak_r.data()->readLine();
            emit generatedUninstallCommandOutput(line);
        }});

    QObject::connect(pak_r.data(), QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred),
        [=](QProcess::ProcessError process_error){  QMessageBox::warning(new QWidget, tr("Uninstallation"), tr("Packages couln't be removed: %1").arg(pak_r.data()->error()), QMessageBox::Ok); });
    QObject::connect(pak_r.data(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [=](int exit_code, QProcess::ExitStatus exit_status){
        emit finishedUninstall(exit_code, exit_status); });
}


void PackagesManager::clean()
{
    int answer = QMessageBox::information(new QWidget, tr("Clean"),
                                          tr("Are you sure you want to clean after packages installations"),
                                          QMessageBox::Yes | QMessageBox::No);

    if (static_cast<QMessageBox::StandardButton>(answer) == QMessageBox::No)
        return;

    emit acceptedTask(Task::Clean);

    QSharedPointer<QProcess> pak_clean(QSharedPointer<QProcess>(new QProcess));
    pak_clean->start("/bin/bash", QStringList() << "-c" << "pak -Sc");
    QObject::connect(pak_clean.data(), &QProcess::readyReadStandardOutput, [=]() {
        while (pak_clean.data()->canReadLine())
        {
            QString line = pak_clean.data()->readLine();
            emit generatedCleanCommandOutput(line);
        }});

    QObject::connect(pak_clean.data(), QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred),
        [=](QProcess::ProcessError process_error){ QMessageBox::warning(new QWidget, tr("Clean"), tr("Packages couln't be cleaned: %1").arg(pak_clean.data()->error()), QMessageBox::Ok); });
    QObject::connect(pak_clean.data(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [=](int exit_code, QProcess::ExitStatus exit_status){
        emit finishedClean(exit_code, exit_status); });
}


void PackagesManager::updateMirrors()
{
    int answer = QMessageBox::information(new QWidget, tr("Update mirrors"),
                                          tr("Are you sure you want to update mirrors?"),
                                          QMessageBox::Yes | QMessageBox::No);

    if (static_cast<QMessageBox::StandardButton>(answer) == QMessageBox::No)
        return;

    emit acceptedTask(Task::MirrorsUpdate);

    QSharedPointer<QProcess> pak_clean(QSharedPointer<QProcess>(new QProcess));
    pak_clean->start("/bin/bash", QStringList() << "-c" << "pak -m");
    QObject::connect(pak_clean.data(), &QProcess::readyReadStandardOutput, [=]() {
        while (pak_clean.data()->canReadLine())
        {
            QString line = pak_clean.data()->readLine();
            emit generatedMirrorsUpdateCommandOutput(line);
        }});

    QObject::connect(pak_clean.data(), QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred),
        [=](QProcess::ProcessError process_error){ QMessageBox::warning(new QWidget, tr("Update mirrors"), tr("Mirrors couldn't be updated: %1").arg(pak_clean.data()->error()), QMessageBox::Ok); });
    QObject::connect(pak_clean.data(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [=](int exit_code, QProcess::ExitStatus exit_status){
        emit finishedMirrorsUpdate(exit_code, exit_status); });
}


void PackagesManager::updateAll()
{
    int answer = QMessageBox::information(new QWidget, tr("Update all"),
                                          tr("Are you sure you want to update all packages?"),
                                          QMessageBox::Yes | QMessageBox::No);

    if (static_cast<QMessageBox::StandardButton>(answer) == QMessageBox::No)
        return;

    emit acceptedTask(Task::UpdateAll);

    QSharedPointer<QProcess> pak_clean(QSharedPointer<QProcess>(new QProcess));
    pak_clean->start("/bin/bash", QStringList() << "-c" << "pak -Su");
    QObject::connect(pak_clean.data(), &QProcess::readyReadStandardOutput, [=]() {
        while (pak_clean.data()->canReadLine())
        {
            QString line = pak_clean.data()->readLine();
            emit generatedUpdateAllCommandOutput(line);
        }});

    QObject::connect(pak_clean.data(), QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred),
        [=](QProcess::ProcessError process_error){ QMessageBox::warning(new QWidget, tr("Update all"), tr("All packages couldn't b updated: %1").arg(pak_clean.data()->error()), QMessageBox::Ok); });
    QObject::connect(pak_clean.data(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [=](int exit_code, QProcess::ExitStatus exit_status){
        emit finishedUpdateAll(exit_code, exit_status); });
}


void PackagesManager::printInstalledVCSPackages()
{
    int answer = QMessageBox::information(new QWidget, tr("Print vcs packages"),
                                          tr("Are you sure you want to print all vcs packages?"),
                                          QMessageBox::Yes | QMessageBox::No);

    if (static_cast<QMessageBox::StandardButton>(answer) == QMessageBox::No)
        return;

    emit acceptedTask(Task::PrintVCSPackages);

    QSharedPointer<QProcess> pak_clean(QSharedPointer<QProcess>(new QProcess));
    pak_clean->start("/bin/bash", QStringList() << "-c" << "pak --vcs");
    QObject::connect(pak_clean.data(), &QProcess::readyReadStandardOutput, [=]() {
        while (pak_clean.data()->canReadLine())
        {
            QString line = pak_clean.data()->readLine();
            emit generatedPrintVCSPackagesCommandOutput(line);
        }});

    QObject::connect(pak_clean.data(), QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred),
        [=](QProcess::ProcessError process_error){ QMessageBox::warning(new QWidget, tr("Print vcs packages"), tr("Printing installed vcs packages ended without success: %1").arg(pak_clean.data()->error()), QMessageBox::Ok); });
    QObject::connect(pak_clean.data(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [=](int exit_code, QProcess::ExitStatus exit_status){
        emit finishedVCSPackagesPrint(exit_code, exit_status); });
}


void PackagesManager::updateInstalledPackages()
{
    int answer = QMessageBox::information(new QWidget, tr("Installed packages update"),
                                          tr("Are you sure you want to update installed packages?"),
                                          QMessageBox::Yes | QMessageBox::No);

    if (static_cast<QMessageBox::StandardButton>(answer) == QMessageBox::No)
        return;

    emit acceptedTask(Task::UpdateInstalledPackages);

    QSharedPointer<QProcess> pak_clean(QSharedPointer<QProcess>(new QProcess));
    pak_clean->start("/bin/bash", QStringList() << "-c" << "pak -Sy");
    QObject::connect(pak_clean.data(), &QProcess::readyReadStandardOutput, [=]() {
        while (pak_clean.data()->canReadLine())
        {
            QString line = pak_clean.data()->readLine();
            emit generatedInstalledPackagesUpdateCommandOutput(line);
        }});

    QObject::connect(pak_clean.data(), QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred),
        [=](QProcess::ProcessError process_error){ QMessageBox::warning(new QWidget, tr("Installed packages update"), tr("Update of installed packages ended without success: %1").arg(pak_clean.data()->error()), QMessageBox::Ok); });
    QObject::connect(pak_clean.data(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [=](int exit_code, QProcess::ExitStatus exit_status){
        emit finishedInstalledPackagesUpdate(exit_code, exit_status); });
}
