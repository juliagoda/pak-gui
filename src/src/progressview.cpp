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

#include "progressview.h"

#include "logger.h"

#include <QLineEdit>
#include <QPushButton>


ProgressView::ProgressView(QDialog* parent)
    : QDialog(parent),
    process(nullptr)
{
    m_ui.setupUi(this);
    m_ui.progress_view_tabwidget->clear();
}


ProgressView::~ProgressView()
{
    manual_input_widgets.clear();
}


void ProgressView::addProgressView(QWidget* progress_view)
{
    if (!progress_view)
        return;

    Logger::logger()->logDebug(QStringLiteral("Generated operation tab in preview window titled \"%1\"").arg(progress_view->objectName()));
    m_ui.progress_view_tabwidget->addTab(progress_view, progress_view->objectName());
}


void ProgressView::createSignals(Process::Task task, QSharedPointer<Process> new_process)
{
    process = new_process;
    auto task_text = QVariant::fromValue(task).toString().toLower();
    manual_input_widgets.insert(m_ui.progress_view_tabwidget->currentWidget()->objectName(),
                                {m_ui.progress_view_tabwidget->currentWidget()->findChild<QLineEdit*>(QString("input_for_%1_lineedit").arg(task_text)),
                                 m_ui.progress_view_tabwidget->currentWidget()->findChild<QPushButton*>(QString("input_for_%1_btn").arg(task_text))});
    tasks_map.insert(m_ui.progress_view_tabwidget->currentWidget()->objectName(), task);

    QObject::connect(manual_input_widgets.value(m_ui.progress_view_tabwidget->currentWidget()->objectName()).first, &QLineEdit::textChanged, this, [this](const QString& text)
                     { text.isEmpty() ? manual_input_widgets.value(m_ui.progress_view_tabwidget->currentWidget()->objectName()).second->setEnabled(false) : manual_input_widgets.value(m_ui.progress_view_tabwidget->currentWidget()->objectName()).second->setEnabled(true); });
    QObject::connect(manual_input_widgets.value(m_ui.progress_view_tabwidget->currentWidget()->objectName()).second, &QPushButton::clicked, process.data(), [this](bool)
                     { process->inputAnswer(manual_input_widgets.value(m_ui.progress_view_tabwidget->currentWidget()->objectName()).first->text(),
                       tasks_map.value(m_ui.progress_view_tabwidget->currentWidget()->objectName())); });
}


void ProgressView::removeProgressView(QWidget* progress_view)
{
    if (!progress_view)
        return;

    int index = m_ui.progress_view_tabwidget->indexOf(progress_view);

    if (index == -1)
    {
        Logger::logger()->logWarning(QStringLiteral("progress view titled \"%1\" couldn't be removed from tabwidget window - couldn't be found").arg(progress_view->objectName()));
        return;
    }

    Logger::logger()->logDebug(QStringLiteral("Removing tab widget titled \"%1\"").arg(progress_view->objectName()));
    m_ui.progress_view_tabwidget->removeTab(index);
}


int ProgressView::tabsCount()
{
    return m_ui.progress_view_tabwidget->count();
}
