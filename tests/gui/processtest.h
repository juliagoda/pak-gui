// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of tests for CachyOS package manager (based on "pak" application).
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

#include "process.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class TestProcess : public QObject
{
    Q_OBJECT

public:
    TestProcess(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockProcess process;
    QSharedPointer<ActionsAccessChecker> actions_checker{nullptr};
};

