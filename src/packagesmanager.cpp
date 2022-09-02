#include "packagesmanager.h"
#include "qmessagebox.h"

#include <QDir>
#include <QSharedPointer>


PackagesManager::PackagesManager()
{

}


void PackagesManager::update(QStringList checked_packages)
{
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
