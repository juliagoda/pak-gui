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

