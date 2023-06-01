#pragma once

#include "choicewindow.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockChoiceWindow : public ChoiceWindow
{
    Q_OBJECT

public:
    explicit MockChoiceWindow(const QString& new_title,
                              QDialog* new_parent = nullptr);
    friend class TestChoiceWindow;
};


class TestChoiceWindow : public QObject
{
    Q_OBJECT

public:
    TestChoiceWindow(QObject* parent = nullptr);

private slots:
    void isSpinningAnimationRunningOnStart();
    void isSpinningAnimationStoppedAfterComboBoxFillWithList();
    void isSpinningAnimationStoppedAfterComboBoxFillWithText();
    void isOkButtonDisabledOnStart();
    void isOkButtonEnabledAfterChoice();
    void isChoiceDefinedSignalEmittedAfterOkButtonPress();
    void cleanup();

private:
    MockChoiceWindow choice_window;
};
