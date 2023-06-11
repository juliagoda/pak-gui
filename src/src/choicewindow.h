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

#include "ui_choicewindow.h"
#include "spinninganimation.h"
#include "outputfilter.h"

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

protected Q_SLOTS:
    void showNoResults();

signals:
    bool choiceDefined(QString choice);
    bool choiceDefined(int new_index);
    void filledOptionsBox();
    void cancelled();

protected:
    QWeakPointer<SpinningAnimation> retrieveSpinningAnimation();
    void init();
    Ui::ChoiceWindow* retrieveUi();
    void clearComboBox();


private:
    Ui::ChoiceWindow m_ui;
    QString title;
    QSharedPointer<SpinningAnimation> spinning_animation = QSharedPointer<SpinningAnimation>(new SpinningAnimation);
    QScopedPointer<OutputFilter> output_filter = QScopedPointer<OutputFilter>(new OutputFilter);
};

