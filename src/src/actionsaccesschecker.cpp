// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of CachyOS package manager based on "pak" application.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "actionsaccesschecker.h"

#include "defs.h"
#include "logger.h"

#include <KLocalizedString>
#include <QProcess>
#include <QDir>
#include <QNetworkInterface>
#include <QMessageBox>

#include <numeric>


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
    Logger::logger()->logFatal(QStringLiteral("Required packages are missing:\n\n %1").arg(not_installed_packages.join("\n")));

#ifdef RUN_TESTS
    return;
#endif

    QMessageBox::critical(parent, i18np("Missing package", "Missing packages", not_installed_packages.join("\n").size()),
                          i18np("Required package is missing:\n\n%2", "Required packages are missing:\n\n%2",
                                not_installed_packages.join("\n").count(), not_installed_packages.join("\n")));
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
    pak_download->waitForStarted(2000);
    pak_download->waitForFinished(2000);
    auto result = QString::fromUtf8(pak_download->readAll());
    pak_download->kill();
    return result.contains(QRegExp(package_name + "\\s+\\d+.*"));
}


bool ActionsAccessChecker::checkNetworkInterfaces() const
{
    auto all_interfaces = QNetworkInterface::allInterfaces();
    return std::any_of(all_interfaces.cbegin(), all_interfaces.cend(), [](const QNetworkInterface& iNetInterface)
    {
        return (iNetInterface.type() != QNetworkInterface::Loopback &&
                iNetInterface.flags().testFlag(QNetworkInterface::IsUp) &&
                iNetInterface.flags().testFlag(QNetworkInterface::IsRunning));
    });
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
    return std::accumulate(required_packages.cbegin(), required_packages.cend(), QStringList{},
                           [this](QStringList list, const QString& package)
    {
        if (!findPackage(package))
            list.append(package);

        return list;
    });
}
