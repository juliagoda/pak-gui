#include "installcommandparser.h"

#include <QSharedPointer>

InstallCommandParser::InstallCommandParser() :
    package_name(""),
    current_task(),
    sourceToTaskMap()
{
    init();
}


void InstallCommandParser::init()
{
    sourceToTaskMap.insert(QString("AUR"), Process::Task::InstallAfterSearchAUR);
    sourceToTaskMap.insert(QString("POLAUR"), Process::Task::InstallAfterSearchPOLAUR);
    sourceToTaskMap.insert(QString("Repositories"), Process::Task::InstallAfterSearchRepo);
}


void InstallCommandParser::updatePackageName(const QString& new_package_name)
{
    package_name = new_package_name;
}


void InstallCommandParser::updateTask(const QString& source_name)
{
    if (!sourceToTaskMap.contains(source_name))
    {
        current_task = Process::Task::InstallAfterSearchRepo;
        return;
    }

    current_task = sourceToTaskMap.value(source_name);
}


QString InstallCommandParser::getPackageName()
{
    return package_name;
}


QStringList InstallCommandParser::retrieveInfo()
{
    return QStringList();
}


void InstallCommandParser::start(QSharedPointer<Process>& process,
                                 uint packages_to_update)
{
    process->setPackagesToUpdate(packages_to_update);

    if (process->preparedBeforeRun(current_task, QStringList() << package_name))
        process->run(current_task, QStringList() << package_name);
}
