// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of  package manager based on "pak" application.
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

#include "package.h"

#include <QString>


class SiPackage : public Package
{
public:
    explicit SiPackage(const QString& package_content);
    SiPackage(const SiPackage& si_package);
    SiPackage& operator=(const SiPackage& si_package);
    SiPackage(SiPackage&& si_package);
    SiPackage& operator=(SiPackage&& si_package);
    ~SiPackage() override = default;

    QListWidgetItem* clone() const override;
    const QString& getRepo() const { return repo; };

private:
    void updateDataSi(const QString& package_content, int name_line, int version_line);
    void setRepo(const QString& new_repo) { repo = new_repo; };
    void setRepoParameter(const QStringList& lines);
    void setNameParameter(const QStringList& lines);
    void setVersionParameter(const QStringList& lines);

    QString repo;
};
