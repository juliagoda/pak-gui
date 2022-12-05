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


ActionsAccessChecker::ActionsAccessChecker(QWidget* new_parent) :
    required_packages(),
    is_asp_installed(false),
    is_auracle_installed(false),
    is_reflector_installed(false),
    is_git_installed(false),
    is_online(true),
    parent(new_parent)
{
    required_packages << PAK_EXEC_FILE << PACMAN_EXEC_FILE << PACMAN_CONTRIB_EXEC_FILE << KDESU_EXEC_FILE << KSSHASKPASS_EXEC_FILE;
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
    QString prefix = package_name;
    QString filtered_prefix = prefix.remove(QRegExp("-"));
    QDir::setSearchPaths(filtered_prefix, QStringList() << QDir::currentPath() << QString(getenv("PATH")).split(":"));
    QFile executable(filtered_prefix + ":" + package_name);
    return executable.exists();
}


ActionsAccessChecker *ActionsAccessChecker::actionsAccessChecker(QWidget* new_parent)
{
    mutex.lock();
    if (instance == nullptr)
        instance = new ActionsAccessChecker(new_parent);

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

    QStringList::iterator it;
    for(it = required_packages.begin(); it != required_packages.end(); it++)
    {
        if (!findPackage(*it))
            not_installed_packages.append(*it);
    }

    return not_installed_packages;
}


void ActionsAccessChecker::findRequiredPackages()
{
    QStringList not_installed_packages = getNotInstalledPackagesList();
    if (!not_installed_packages.isEmpty())
    {
        QMessageBox::critical(parent, i18n("Missing packages"), i18n("Required packages are missing:\n\n") +
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

        if (is_online)
            break;
    }

    if (connection_state_changed != is_online)
    {
        Logger::logger()->logWarning(QStringLiteral("Application has been turned into %1 state").arg(is_online ? "online" : "offline"));
        emit internetAccessChanged(is_online);
        connection_state_changed = is_online;
    }
}

void ActionsAccessChecker::emitSignals()
{
    emit aspAccessChanged(is_asp_installed);
    emit auracleAccessChanged(is_auracle_installed);
    emit reflectorAccessChanged(is_reflector_installed);
    emit gitAccessChanged(is_git_installed);
}
