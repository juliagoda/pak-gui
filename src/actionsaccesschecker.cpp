#include "actionsaccesschecker.h"
#include "defs.h"

#include <KLocalizedString>
#include <QProcess>
#include <QDir>
#include <QNetworkInterface>
#include <QMessageBox>


ActionsAccessChecker* ActionsAccessChecker::instance{nullptr};
QMutex ActionsAccessChecker::mutex;


ActionsAccessChecker::ActionsAccessChecker() :
    is_asp_installed(false),
    is_auracle_installed(false),
    is_reflector_installed(false),
    is_git_installed(false),
    is_online(false)
{
    qInfo() << "Environment variable PATH: " << QString(getenv("PATH")).split(":");
}


ActionsAccessChecker::~ActionsAccessChecker()
{
   mutex.unlock();
}


void ActionsAccessChecker::run()
{
    findRequiredPackages();
    is_asp_installed = findPackage(ASP_EXEC_FILE);
    is_auracle_installed = findPackage(AURACLE_EXEC_FILE);
    is_reflector_installed = findPackage(REFLECTOR_EXEC_FILE);
    is_git_installed = findPackage(GIT_EXEC_FILE);

    checkInternetConnection();
    emitSignals();
}


bool ActionsAccessChecker::findPackage(const QString& package_name)
{
    QDir::setSearchPaths(package_name, QStringList() << QDir::currentPath() << QString(getenv("PATH")).split(":"));
    QFile executable(package_name + ":" + package_name);
    return executable.exists();
}


ActionsAccessChecker *ActionsAccessChecker::actionsAccessChecker()
{
    mutex.lock();
    if (instance == nullptr)
        instance = new ActionsAccessChecker();

    return instance;
}

bool ActionsAccessChecker::isAspInstalled() const
{
    return is_asp_installed;
}


bool ActionsAccessChecker::isAuracleInstalled() const
{
    return is_auracle_installed;
}


bool ActionsAccessChecker::isReflectorInstalled() const
{
    return is_reflector_installed;
}


bool ActionsAccessChecker::isGitInstalled() const
{
    return is_git_installed;
}


bool ActionsAccessChecker::isOnline() const
{
    return is_online;
}


void ActionsAccessChecker::findRequiredPackages()
{
    if (!findPackage(PAK_EXEC_FILE) || !findPackage(PACMAN_EXEC_FILE) || !findPackage(PACMAN_CONTRIB_EXEC_FILE))
    {
        QMessageBox::critical(new QWidget, i18n("Missing packages"), i18n("Required packages are missing."
                                                                          "Check if all of them:\n\"pak\"\n\"pacman\"\n\"pacman-contrib\\n\n"
                                                                          "are installed before application start!"));
        emit requiredPackagesNotFound();
    }
}


void ActionsAccessChecker::checkInternetConnection()
{
    for(const QNetworkInterface& interface : QNetworkInterface::allInterfaces())
    {
        if (interface.type() == QNetworkInterface::Loopback)
            continue;
        is_online = interface.flags().testFlag(QNetworkInterface::IsUp) &&
                interface.flags().testFlag(QNetworkInterface::IsRunning);
        if (is_online)
            break;
    }
}


void ActionsAccessChecker::emitSignals()
{
    emit aspAccessChanged(is_asp_installed);
    emit auracleAccessChanged(is_auracle_installed);
    emit reflectorAccessChanged(is_reflector_installed);
    emit gitAccessChanged(is_git_installed);
    emit internetAccessChanged(is_online);
}
