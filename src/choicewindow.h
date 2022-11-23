#pragma once

#include "ui_choicewindow.h"

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QMovie>


class ChoiceWindow : public QDialog
{
    Q_OBJECT

public:
    ChoiceWindow(const QString& new_title,
                 QDialog* new_parent = nullptr);

    ~ChoiceWindow() = default;

public Q_SLOTS:
    void toggleOkButton(int new_index);
    void fillComboBox(QString& output);
    void stopAnimation();

signals:
    bool choiceDefined(int new_index);
    void filledOptionsBox();

private:
    void startAnimation();
    void init();

    Ui::ChoiceWindow m_ui;
    QString title;
    QSharedPointer<QMovie> spinning_animation;
};

