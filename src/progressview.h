#pragma once

#include "ui_progressview.h"

#include <QWidget>

class ProgressView : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressView(QDialog* parent = nullptr);

    void addProgressView(QWidget* progress_view);
    void removeProgressView(QWidget* progress_view);

private:
    Ui::ProgressView m_ui;

};
