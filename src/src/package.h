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

#pragma once

#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <QRegularExpression>


class Package : public QListWidgetItem
{
public:
    enum class Source
    {
        Repo = 0,
        AUR,
        POLAUR,
        Unknown
    };

    enum class TooltipLine
    {
        Name = 0,
        Version,
        Description,
        Architecture,
        URL,
        Licenses,
        Groups,
        Provides,
        DependsOn,
        OptionalDeps,
        ConflictsWith,
        Replaces,
        DownloadSize,
        RequiredBy,
        OptionalFor,
        InstalledSize,
        Packager,
        BuildDate,
        InstallDate,
        InstallReason,
        InstallScript,
        ValidatedBy,
        Unknown
    };

    Package(const QString& package_content, Source new_source);

    Package(Package& package);

    ~Package() override = default;

    virtual int getNo() const;
    virtual const QString& getName() const;
    virtual const QString& getVersion() const;
    virtual Package::Source getSource() const;

    virtual void setNo(const int new_no);

protected:
    virtual void updateData(const QString& package_content, int name_line, int version_line);

    void setToolTipOnPackage(const QString& text);

    bool validate(const QStringList& lines, int expected_size, const QString& funtion_name);

    virtual void setName(const QString& new_name);
    virtual void setVersion(const QString& new_version);
    virtual void setSource(Source new_source);
    virtual void buildTooltipsLinesMap();

    QString name{};
    QString version{};
    Package::Source source{Package::Source::Repo};
    QHash<int, TooltipLine> numberToTooltipLine{};
    int no{0};

private:
    void setNameParameter(int parameter_line,
                          const QStringList& lines);

    void setVersionParameter(int parameter_line,
                             const QStringList& lines);
};
