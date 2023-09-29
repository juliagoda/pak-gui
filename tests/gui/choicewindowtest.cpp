// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of tests for  package manager (based on "pak" application).
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

#include "choicewindowtest.h"

#include <QPushButton>
#include <QDialogButtonBox>


MockChoiceWindow::MockChoiceWindow(const QString& new_title,
                                   QDialog* new_parent) :
    ChoiceWindow{new_title, new_parent}
{
   // ...
}


TestChoiceWindow::TestChoiceWindow(QObject* parent) :
    QObject{parent},
    choice_window{QString()}
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestChoiceWindow::isSpinningAnimationRunningOnStart()
{
    QVERIFY(choice_window.retrieveSpinningAnimation().toStrongRef()->isSmallAnimationRunning());
}


void TestChoiceWindow::isSpinningAnimationStoppedAfterComboBoxFillWithList()
{
    QStringList choice_options{QStringList() << "option1" << "option2"};
    choice_window.fillComboBox(choice_options);
    QVERIFY(!choice_window.retrieveSpinningAnimation().toStrongRef()->isSmallAnimationRunning());
}


void TestChoiceWindow::isSpinningAnimationStoppedAfterComboBoxFillWithText()
{
    QString choice_options{QString("option1\noption2")};
    choice_window.fillComboBox(choice_options);
    QVERIFY(!choice_window.retrieveSpinningAnimation().toStrongRef()->isSmallAnimationRunning());
}


void TestChoiceWindow::isOkButtonDisabledOnStart()
{
    QVERIFY(!choice_window.retrieveUi()->buttonBox->button(QDialogButtonBox::Ok)->isEnabled());
}


void TestChoiceWindow::isOkButtonEnabledAfterChoice()
{
    QStringList choice_options{QStringList() << "[option1]" << "[option2]"};
    choice_window.fillComboBox(choice_options);
    QTest::keyClicks(choice_window.retrieveUi()->choice_combo_box, "option1");

    QVERIFY(choice_window.retrieveUi()->buttonBox->button(QDialogButtonBox::Ok)->isEnabled());
}


void TestChoiceWindow::isChoiceDefinedSignalEmittedAfterOkButtonPress()
{
    QSignalSpy choice_defined_signal_text(&choice_window, SIGNAL(choiceDefined(QString)));
    QSignalSpy choice_defined_signal_index(&choice_window, SIGNAL(choiceDefined(int)));

    QStringList choice_options{QStringList() << "[option1]" << "[option2]"};
    choice_window.fillComboBox(choice_options);
    QTest::keyClicks(choice_window.retrieveUi()->choice_combo_box, "option1");
    QTest::mouseClick(choice_window.retrieveUi()->buttonBox->button(QDialogButtonBox::Ok), Qt::LeftButton);

    QCOMPARE(choice_defined_signal_text.count(), 1);
    QCOMPARE(choice_defined_signal_index.count(), 1);
}


void TestChoiceWindow::cleanup()
{
    constexpr int choice_index = 0;
    choice_window.clearComboBox();
    choice_window.toggleOkButton(choice_index);
}
