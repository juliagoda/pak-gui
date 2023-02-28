#pragma once

#include "ui_choicewindow.h"
#include "spinninganimation.h"

#include <QWidget>
#include <QString>
#include <QStringList>


class ChoiceWindow : public QDialog
{
    Q_OBJECT

public:
    ChoiceWindow(const QString& new_title,
                 QDialog* new_parent = nullptr);

    ~ChoiceWindow() override;

public Q_SLOTS:
    void toggleOkButton(int new_index);
    void fillComboBox(QString& output);
    void fillComboBox(QStringList output_list);

signals:
    bool choiceDefined(QString choice);
    bool choiceDefined(int new_index);
    void filledOptionsBox();

protected:
    QWeakPointer<SpinningAnimation> retrieveSpinningAnimation();
    void init();
    Ui::ChoiceWindow* retrieveUi();
    void clearComboBox();

private:
    Ui::ChoiceWindow m_ui;
    QString title;
    QSharedPointer<SpinningAnimation> spinning_animation = QSharedPointer<SpinningAnimation>(new SpinningAnimation);
};

