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

#include "choicewindow.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockChoiceWindow : public ChoiceWindow
{
    Q_OBJECT

public:
    explicit MockChoiceWindow(const QString& new_title,
                              QDialog* new_parent = nullptr);
    friend class TestChoiceWindow;
};


class TestChoiceWindow : public QObject
{
    Q_OBJECT

public:
    TestChoiceWindow(QObject* parent = nullptr);

private slots:
    void isSpinningAnimationRunningOnStart();
    void isSpinningAnimationStoppedAfterComboBoxFillWithList();
    void isSpinningAnimationStoppedAfterComboBoxFillWithText();
    void isOkButtonDisabledOnStart();
    void isOkButtonEnabledAfterChoice();
    void isChoiceDefinedSignalEmittedAfterOkButtonPress();
    void cleanup();

private:
    MockChoiceWindow choice_window;
};
