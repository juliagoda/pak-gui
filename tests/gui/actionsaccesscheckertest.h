// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of tests for  package manager (based on "pak" application).
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

#include "actionsaccesschecker.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockActionsAccessChecker : public ActionsAccessChecker
{
    Q_OBJECT

public:
    explicit MockActionsAccessChecker(QWidget* new_parent);
    ~MockActionsAccessChecker() override = default;
    friend class TestActionsAccessChecker;
    void showRequiredPackagesNotFoundWindow(const QStringList& not_installed_packages) const override;
    bool checkNetworkInterfaces() const override;
};


class TestActionsAccessChecker : public QObject
{
    Q_OBJECT

public:
    TestActionsAccessChecker(QObject* parent = nullptr);

private slots:
    void internetConnectionStateSignalEmittedAfterChange();
    void stopApplicationSendSignalAfterNotFindingRequiredPackages();
    void initiallyPackagesAreNotFound();
    void initiallyInternetConnectionIsOn();
    void properlyFindsExecutableFileWithExampleOfPakQtests();
    void emitSignalFunctionContainsEmitsForFourPackages();
    void cleanup();

private:
    MockActionsAccessChecker actions_access_checker;
};


