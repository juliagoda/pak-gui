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

    void run(Process::Task new_task, QStringList new_checked_packages = QStringList());
    void setPackagesToUpdate(uint packages_to_update_count);
    void setAurPackagesToUpdate(uint packages_to_update_count);
    static bool isAlreadyRunning(Process::Task new_task);
    static void resetRunningTask(Process::Task new_task);

protected:
    virtual void startProcess(Task new_task);
    virtual bool askQuestion(Task new_task, QStringList new_checked_packages);
    void processReadLine(QString& line, Process::Task new_task);

private Q_SLOTS:
    void updateCleanCommand(bool is_auracle_installed);

public Q_SLOTS:
    void inputAnswer(const QString& new_answer);

signals:
    void finished(Process::Task task, int exit_code, QProcess::ExitStatus exit_status);
    void generatedOutput(Process::Task task, const QString& line);
    void acceptedTask(Process::Task task);
    void acceptedMainTask(Process::Task task);
    void showInput(Process::Task task);

private:
    void setDefaultCommands();
    void updateMap(QStringList& checked_packages);
    void prepareMapsForNextTask();
    void emitTask(Process::Task task);
    QString questionForm(QStringList& new_checked_packages, Task new_task);
    void connectSignals(QSharedPointer<QProcess> &process, Task new_task);
    bool isNeededAskAboutUpdate(Task new_task);
    bool getAnswer(Process::Task new_task, QStringList new_checked_packages);
    void updateCurrentCommandForUpdate(Process::Task new_task);
    void replaceAutoAcceptationForTask(Process::Task new_task, const QString& original_form, const QString& acceptation_form);
    void removeAutoAcceptationFromCommand(Process::Task new_task);
    void changeUpdateAllCommand(Process::Task new_task);

    QMap<Task, QPair<QString, QString>> messages_map;
    QMap<Task, QStringList> commands_map;
    QSharedPointer<QProcess> current_process;
    uint packages_to_update = 0;
    uint aur_packages_to_update_count = 0;
    QWidget* parent;
};

