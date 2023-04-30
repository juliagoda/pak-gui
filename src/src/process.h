#pragma once

#include <QObject>
#include <QProcess>
#include <QString>
#include <QMap>
#include <QStringList>
#include <QSharedPointer>


class ActionsAccessChecker;

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
        Update,
        SyncPOLAUR
    };
    Q_ENUM(Task)

    Process(QSharedPointer<ActionsAccessChecker>& new_actions_access_checker, QWidget* new_parent);
    ~Process() override = default;

    void run(Task new_task, QStringList new_checked_packages = QStringList());

protected:
    virtual void startProcess(Task new_task);
    virtual bool askQuestion(Task new_task, QStringList new_checked_packages);
    void processReadLine(QString& line, Process::Task new_task);

private Q_SLOTS:
    void updateCleanCommand(bool is_auracle_installed);

signals:
    void finished(Process::Task task, int exit_code, QProcess::ExitStatus exit_status);
    void generatedOutput(Process::Task task, const QString& line);
    void acceptedTask(Process::Task);
    void acceptedMainTask(Process::Task);

private:
    void updateMap(QStringList& checked_packages);
    void prepareMapsForNextTask();
    void emitTask(Process::Task task);
    QString questionForm(QStringList& new_checked_packages, Task new_task);
    void connectSignals(QSharedPointer<QProcess> &process, Task new_task);
    bool isNeededAskAboutUpdate(Task new_task);
    bool getAnswer(Process::Task new_task, QStringList new_checked_packages);
    void updateCurrentCommandForUpdate(Process::Task new_task, QStringList new_checked_packages);

    QMap<Task, QPair<QString, QString>> messages_map;
    QMap<Task, QStringList> commands_map;
    QWidget* parent;
};

