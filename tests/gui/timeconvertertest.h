#pragma once

#include "timeconverter.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class TestTimeConverter : public QObject
{
    Q_OBJECT

public:
    TestTimeConverter(QObject* parent = nullptr);

private slots:
    void is2MinutesEqualTo120000Milliseconds();
    void is120000MillisecondsEqualTo2Minutes();
    void is2HoursEqualTo7200000Milliseconds();
    void is7200000MillisecondsEqualTo2Hours();
    void is2DaysEqualTo172800000Milliseconds();
    void is172800000MillisecondsEqualTo2Days();
    void is2Days2Hours2MinutesEqualTo180120000Milliseconds();
    void is180120000MillisecondsConvertedToCorrectText();
};



