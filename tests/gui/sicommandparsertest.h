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

#include "sicommandparser.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockSiCommandParser : public SiCommandParser
{
    Q_OBJECT

public:
    explicit MockSiCommandParser() = default;
    friend class TestAvailablePackagesColumn;

    QString generateResult() override;
};


class TestSiCommandParser : public QObject
{
    Q_OBJECT

public:
    TestSiCommandParser(QObject* parent = nullptr);

private slots:
    void initTestCase_data();
    void isListContainingTwoPackages();
    void isListContainingPackagesWithCorrectContent();

private:
    MockSiCommandParser si_command_parser;
};
