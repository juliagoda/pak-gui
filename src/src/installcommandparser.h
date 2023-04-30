#pragma once

#include "commandparser.h"
#include "process.h"

#include <QString>
#include <QMap>


class InstallCommandParser : public CommandParser
{
    Q_OBJECT

public:
    InstallCommandParser();
    ~InstallCommandParser() override = default;

    void updatePackageName(const QString &new_package_name);
    void updateTask(const QString& source_name);
    QString getPackageName();
    QStringList retrieveInfo() override;
    virtual void start(QSharedPointer<Process>& process,
                       uint packages_to_update = 0);

private:
    void init();

    QString package_name;
    Process::Task current_task;
    QMap<QString, Process::Task> sourceToTaskMap;
};

