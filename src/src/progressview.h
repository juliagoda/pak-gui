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

#include "ui_progressview.h"
#include "process.h"

#include <QWidget>
#include <QPointer>
#include <QLineEdit>
#include <QPushButton>

class ProgressView : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressView(QDialog* parent = nullptr);
    ~ProgressView() override;

    void addProgressView(QWidget* progress_view);
    void createSignals(Process::Task task, QSharedPointer<Process> process);
    void removeProgressView(QWidget* progress_view);
    int tabsCount();

private:
    Ui::ProgressView m_ui;

    QMap<QString, QPair<QLineEdit*, QPushButton*>> manual_input_widgets;
    QMap<QString, Process::Task> tasks_map;
    QSharedPointer<Process> process;
};

