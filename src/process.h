#pragma once

#include <QObject>
#include <QProcess>
#include <QString>
#include <QMap>
#include <QStringList>

class Process : public QObject
{
    Q_OBJECT

public:
    enum class Task
    {
        Clean,
        MirrorsUpdate,
        UpdateAll,
        PrintVCSPackages,
        UpdateInstalledPackages,
        Uninstall,
        Install,
        Update
    };
    Q_ENUM(Task)

    Process(Task new_task, QStringList new_checked_packages = QStringList());
    void run();

signals:
    void finished(int exit_code, QProcess::ExitStatus exit_status);
    void generatedOutput(const QString& line);

private:
    Task task;
    QMap<Task, QPair<QString, QString>> messages_map;
    QMap<Task, QStringList> commands_map;
};

