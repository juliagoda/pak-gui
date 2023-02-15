#pragma once

#include "ui_progressview.h"

#include <QWidget>

class ProgressView : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressView(QDialog* parent = nullptr);
    ~ProgressView() override = default;

    void addProgressView(QWidget* progress_view);
    void removeProgressView(QWidget* progress_view);
    int tabsCount();

private:
    Ui::ProgressView m_ui;

};

