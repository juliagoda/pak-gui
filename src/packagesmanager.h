#pragma once

#include <QObject>
#include <QStringList>
#include <QProcess>

class PackagesManager : public QObject
{
    Q_OBJECT

public:
    enum class Task
    {
        Clean
    };
    Q_ENUM(Task)

    PackagesManager();
    void update(QStringList checked_packages);
    void install(QStringList checked_packages);
    void uninstall(QStringList checked_packages);
    void clean();

signals:
    void finishedUpdate(int exit_code, QProcess::ExitStatus exit_status);
    void finishedInstall(int exit_code, QProcess::ExitStatus exit_status);
    void finishedUninstall(int exit_code, QProcess::ExitStatus exit_status);
    void finishedClean(int exit_code, QProcess::ExitStatus exit_status);
    void generatedInstallCommandOutput(const QString& line);
    void generatedUninstallCommandOutput(const QString& line);
    void generatedUpdateCommandOutput(const QString& line);
    void generatedCleanCommandOutput(const QString& line);
    void acceptedTask(PackagesManager::Task);
};

