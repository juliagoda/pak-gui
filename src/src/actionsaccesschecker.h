// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of package manager based on "pak" application.
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

#pragma once

#include <QObject>
#include <QMutex>


class ActionsAccessChecker : public QObject
{
    Q_OBJECT

public:
    static ActionsAccessChecker* actionsAccessChecker(QWidget* new_parent);
    virtual ~ActionsAccessChecker() override;
    ActionsAccessChecker(ActionsAccessChecker& instance) = delete;
    void operator=(const ActionsAccessChecker& instance) = delete;

    bool isPkgctlInstalled() const;
    bool isAuracleInstalled() const;
    bool isReflectorInstalled() const;
    bool isGitInstalled() const;
    bool isOnline() const;

public Q_SLOTS:
    void checkRequiredPackages();
    void checkInternetConnection();

signals:
    void pkgctlAccessChanged(bool is_asp_installed);
    void auracleAccessChanged(bool is_auracle_installed);
    void reflectorAccessChanged(bool is_reflector_installed);
    void gitAccessChanged(bool is_git_installed);
    void internetAccessChanged(bool is_online);
    void requiredPackagesNotFound();

protected:
    explicit ActionsAccessChecker(QWidget* new_parent);

    static void fillRequiredPackagesList(const QStringList& required_packages);
    virtual void showRequiredPackagesNotFoundWindow(const QStringList& not_installed_packages) const;
    void findRequiredPackages();
    void updateIsOnline(bool new_is_online);
    void emitSignals();
    bool existsPackageByPromptVersion(const QString& package_name);

    virtual bool checkNetworkInterfaces() const;
    bool findPackage(const QString& package_name);
    QStringList getNotInstalledPackagesList();

private:
    bool is_pkgctl_installed = false;
    bool is_auracle_installed = false;
    bool is_reflector_installed = false;
    bool is_git_installed = false;
    bool is_online = true;
    QWidget* parent = nullptr;

    static QStringList required_packages;
    static ActionsAccessChecker* instance;
    static QMutex mutex;
};

