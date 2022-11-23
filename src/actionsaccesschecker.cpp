#include "actionsaccesschecker.h"

#include <QProcess>
#include <QNetworkInterface>

ActionsAccessChecker::ActionsAccessChecker() :
    is_asp_installed(false),
    is_auracle_installed(false),
    is_reflector_installed(false),
    is_git_installed(false),
    is_online(false)
{

}


void ActionsAccessChecker::update()
{
#ifdef ASP_FOUND
    is_asp_installed = true;
#endif

#ifdef AURACLE_GIT_FOUND
    is_auracle_installed = true;
#endif

#ifdef REFLECTOR_FOUND
    is_reflector_installed = true;
#endif

#ifdef GIT_FOUND
    is_git_installed = true;
#endif

    checkInternetConnection();
    emitSignals();
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


void ActionsAccessChecker::checkInternetConnection()
{
    for(const QNetworkInterface& interface : QNetworkInterface::allInterfaces())
    {
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
