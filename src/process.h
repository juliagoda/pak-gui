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
        InstallAfterSearchRepo,
        InstallAfterSearchAUR,
        InstallAfterSearchPOLAUR,
        Update
    };
    Q_ENUM(Task)

    Process();
    void run(Task new_task,
             QStringList new_checked_packages = QStringList());

signals:
    void finished(Process::Task task, int exit_code, QProcess::ExitStatus exit_status);
    void generatedOutput(Process::Task task, const QString& line);
    void acceptedTask(Process::Task);

private:
    void updateMap(QStringList& checked_packages);
    void prepareMapForNextTask();
    void emitSideTask(Process::Task task);
    QString questionForm(QStringList& new_checked_packages, Task new_task);
    bool askQuestion(Task new_task, QStringList new_checked_packages);
    void startProcess(Task new_task);
    void connectSignals(QSharedPointer<QProcess> &process, Task new_task);

    QMap<Task, QPair<QString, QString>> messages_map;
    QMap<Task, QStringList> commands_map;
};

