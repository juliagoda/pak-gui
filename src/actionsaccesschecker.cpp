#include "actionsaccesschecker.h"
#include "defs.h"
#include "logger.h"

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
    Logger::logger()->logInfo(QStringLiteral("Environment variable PATH: %1").arg(QString(getenv("PATH"))));
}


ActionsAccessChecker::~ActionsAccessChecker()
{
   mutex.unlock();
}


void ActionsAccessChecker::checkRequiredPackages()
{
    findRequiredPackages();
    is_asp_installed = findPackage(ASP_EXEC_FILE);
    is_auracle_installed = findPackage(AURACLE_EXEC_FILE);
    is_reflector_installed = findPackage(REFLECTOR_EXEC_FILE);
    is_git_installed = findPackage(GIT_EXEC_FILE);
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


QStringList ActionsAccessChecker::getNotInstalledPackagesList()
{
    QStringList not_installed_packages = QStringList();

    if (!findPackage(PAK_EXEC_FILE))
        not_installed_packages.append("pak");

    if (!findPackage(PACMAN_EXEC_FILE))
        not_installed_packages.append("pacman");

    if (!findPackage(PACMAN_CONTRIB_EXEC_FILE))
        not_installed_packages.append("pacman-contrib");

    if (!findPackage(KDESU_EXEC_FILE))
        not_installed_packages.append("kdesu");

    return not_installed_packages;
}


void ActionsAccessChecker::findRequiredPackages()
{
    QStringList not_installed_packages = getNotInstalledPackagesList();
    if (!not_installed_packages.isEmpty())
    {
        QMessageBox::critical(new QWidget, i18n("Missing packages"), i18n("Required packages are missing:\n\n") +
                                                                          not_installed_packages.join("\n"));
        Logger::logger()->logFatal(QStringLiteral("Required packages are missing:\n\n %1").arg(not_installed_packages.join("\n")));
        emit requiredPackagesNotFound();
    }
}


void ActionsAccessChecker::checkInternetConnection()
{
    static bool connection_state_changed = is_online;
    for(const QNetworkInterface& interface : QNetworkInterface::allInterfaces())
    {
        if (interface.type() == QNetworkInterface::Loopback)
            continue;

        is_online = interface.flags().testFlag(QNetworkInterface::IsUp) &&
                interface.flags().testFlag(QNetworkInterface::IsRunning);

        if (connection_state_changed != is_online)
        {
            Logger::logger()->logWarning(QStringLiteral("Application has been turned into %1 state").arg(is_online ? QString("online") : QString("offline")));
            emit internetAccessChanged(is_online);
            connection_state_changed = is_online;
        }

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
}
