#pragma once

#include "process.h"

#include <QObject>
#include <QStringList>
#include <QProcess>

class PackagesManager : public QObject
{
    Q_OBJECT

public:
    PackagesManager();
    void update(QStringList checked_packages);
    void install(QStringList checked_packages);
    void uninstall(QStringList checked_packages);
    void clean();
    void updateMirrors();
    void updateAll();
    void printInstalledVCSPackages();
    void updateInstalledPackages();

signals:
    void finishedUpdate(int exit_code, QProcess::ExitStatus exit_status);
    void finishedInstall(int exit_code, QProcess::ExitStatus exit_status);
    void finishedUninstall(int exit_code, QProcess::ExitStatus exit_status);
    void finishedClean(int exit_code, QProcess::ExitStatus exit_status);
    void finishedMirrorsUpdate(int exit_code, QProcess::ExitStatus exit_status);
    void finishedUpdateAll(int exit_code, QProcess::ExitStatus exit_status);
    void finishedVCSPackagesPrint(int exit_code, QProcess::ExitStatus exit_status);
    void finishedInstalledPackagesUpdate(int exit_code, QProcess::ExitStatus exit_status);
    void generatedInstallCommandOutput(const QString& line);
    void generatedUninstallCommandOutput(const QString& line);
    void generatedUpdateCommandOutput(const QString& line);
    void generatedCleanCommandOutput(const QString& line);
    void generatedMirrorsUpdateCommandOutput(const QString& line);
    void generatedUpdateAllCommandOutput(const QString& line);
    void generatedPrintVCSPackagesCommandOutput(const QString& line);
    void generatedInstalledPackagesUpdateCommandOutput(const QString& line);
    void acceptedTask(Process::Task);
};

