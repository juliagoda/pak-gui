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

    void updatePackageName(const QString &new_package_name);
    void updateTask(const QString& source_name);
    QString getPackageName() { return package_name; };
    QStringList retrieveInfo() override;
    void start(QSharedPointer<Process>& process);

private:
    void init();

    QString package_name;
    Process::Task current_task;
    QMap<QString, Process::Task> sourceToTaskMap;
};

