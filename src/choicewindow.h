#pragma once

#include "ui_choicewindow.h"

#include <QWidget>
#include <QString>
#include <QStringList>


class ChoiceWindow : public QDialog
{
    Q_OBJECT

public:
    ChoiceWindow(const QString& new_title,
                 const QStringList& new_options,
                 QDialog* new_parent = nullptr);

    ~ChoiceWindow() = default;

private Q_SLOTS:
    void toggleOkButton(int new_index);

signals:
    bool choiceDefined(int new_index);

private:
    void init();

    Ui::ChoiceWindow m_ui;
    QString title;
    QStringList options;
};

