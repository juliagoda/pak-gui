#include "actionsaccesschecker.h"

#include "defs.h"
#include "logger.h"

#include <KLocalizedString>
#include <QProcess>
#include <QDir>
#include <QNetworkInterface>
#include <QMessageBox>


ActionsAccessChecker* ActionsAccessChecker::instance{nullptr};
QStringList ActionsAccessChecker::required_packages{};
QMutex ActionsAccessChecker::mutex;


ActionsAccessChecker::ActionsAccessChecker(QWidget* new_parent) :
    parent{new_parent}
{
    Logger::logger()->logInfo(QStringLiteral("Environment variable PATH: %1").arg(QString(getenv("PATH"))));
}


ActionsAccessChecker::~ActionsAccessChecker()
{
   parent = nullptr;
   instance = nullptr;
   mutex.unlock();
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


void ActionsAccessChecker::checkRequiredPackages()
{
    findRequiredPackages();
    is_asp_installed = findPackage(Constants::aspExecFile());
    is_auracle_installed = existsPackageByPromptVersion(Constants::auracleGit());
    is_reflector_installed = findPackage(Constants::reflectorExecFile());
    is_git_installed = findPackage(Constants::gitExecFile());
    emitSignals();
}


void ActionsAccessChecker::checkInternetConnection()
{
    static bool connection_state_changed = is_online;
    updateIsOnline(checkNetworkInterfaces());

    if (connection_state_changed != is_online)
    {
        Logger::logger()->logWarning(QStringLiteral("Application has been turned into %1 state").arg(is_online ? "online" : "offline"));
        emit internetAccessChanged(is_online);
        connection_state_changed = is_online;
    }
}


ActionsAccessChecker* ActionsAccessChecker::actionsAccessChecker(QWidget* new_parent)
{
    mutex.lock();
    if (instance == nullptr)
    {
        instance = new ActionsAccessChecker{new_parent};
        QStringList required_packages_list{QStringList() << Constants::pakExecFile() << Constants::pacmanExecFile() <<
                                                            Constants::pacmanContribExecFile() << Constants::kdesuExecFile() <<
                                                            Constants::ksshAskPassExecFile()};
        fillRequiredPackagesList(required_packages_list);
    }

    return instance;
}


void ActionsAccessChecker::fillRequiredPackagesList(const QStringList& new_required_packages)
{
    required_packages << new_required_packages;
}


void ActionsAccessChecker::showRequiredPackagesNotFoundWindow(const QStringList& not_installed_packages) const
{
    QMessageBox::critical(parent, i18np("Missing package", "Missing packages", not_installed_packages.join("\n").size()),
                          i18np("Required package is missing:\n\n%2", "Required packages are missing:\n\n%2",
                                not_installed_packages.join("\n").count(), not_installed_packages.join("\n")));
    Logger::logger()->logFatal(QStringLiteral("Required packages are missing:\n\n %1").arg(not_installed_packages.join("\n")));
}


void ActionsAccessChecker::findRequiredPackages()
{
    QStringList not_installed_packages{getNotInstalledPackagesList()};
    if (!not_installed_packages.isEmpty())
    {
        showRequiredPackagesNotFoundWindow(not_installed_packages);
        emit requiredPackagesNotFound();
    }
}


void ActionsAccessChecker::updateIsOnline(bool new_is_online)
{
    is_online = new_is_online;
}


void ActionsAccessChecker::emitSignals()
{
    emit aspAccessChanged(is_asp_installed);
    emit auracleAccessChanged(is_auracle_installed);
    emit reflectorAccessChanged(is_online && is_reflector_installed);
    emit gitAccessChanged(is_online && is_git_installed);
}


bool ActionsAccessChecker::existsPackageByPromptVersion(const QString& package_name)
{
    QScopedPointer<QProcess> pak_download;
    pak_download.reset(new QProcess);
    pak_download->setProcessChannelMode(QProcess::MergedChannels);

    if (pak_download.isNull())
        return false;

    pak_download->start("/bin/bash", QStringList() << "-c" << package_name.trimmed() + " --version");
    pak_download->waitForStarted();
    pak_download->waitForFinished();
    auto result = QString::fromUtf8(pak_download->readAll());
    return result.contains(QRegExp(package_name + "\\s+\\d+.*"));
}


bool ActionsAccessChecker::checkNetworkInterfaces() const
{
    auto all_interfaces = QNetworkInterface::allInterfaces();
    for (auto interface = all_interfaces.cbegin(); interface != all_interfaces.cend(); interface++)
    {
        if ((*interface).type() == QNetworkInterface::Loopback)
            continue;

        if ((*interface).flags().testFlag(QNetworkInterface::IsUp) &&
            (*interface).flags().testFlag(QNetworkInterface::IsRunning))
            return true;
    }

    return false;
}


bool ActionsAccessChecker::findPackage(const QString& package_name)
{
    QString prefix{package_name};
    QString filtered_prefix{prefix.remove(QRegExp("-"))};
    QDir::setSearchPaths(filtered_prefix, QStringList() << QDir::currentPath() << QString(getenv("PATH")).split(":"));
    QFile executable{filtered_prefix + ":" + package_name};
    return executable.exists();
}


QStringList ActionsAccessChecker::getNotInstalledPackagesList()
{
    QStringList not_installed_packages{};

    for (auto it = required_packages.cbegin(); it != required_packages.cend(); it++)
    {
        if (!findPackage(*it))
            not_installed_packages.append(*it);
    }

    return not_installed_packages;
}
