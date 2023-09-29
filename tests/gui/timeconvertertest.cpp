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

#include "timeconvertertest.h"



TestTimeConverter::TestTimeConverter(QObject* parent) :
    QObject{parent}
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestTimeConverter::is2MinutesEqualTo120000Milliseconds()
{
    QCOMPARE(TimeConverter::minutesToMilliseconds(2), 120000);
}


void TestTimeConverter::is120000MillisecondsEqualTo2Minutes()
{
    QCOMPARE(TimeConverter::millisecondsToMinutes(120000), 2);
}


void TestTimeConverter::is2HoursEqualTo7200000Milliseconds()
{
    QCOMPARE(TimeConverter::hoursToMilliseconds(2), 7200000);
}


void TestTimeConverter::is7200000MillisecondsEqualTo2Hours()
{
    QCOMPARE(TimeConverter::millisecondsToHours(7200000), 2);
}


void TestTimeConverter::is2DaysEqualTo172800000Milliseconds()
{
    QCOMPARE(TimeConverter::daysToMilliseconds(2), 172800000);
}


void TestTimeConverter::is172800000MillisecondsEqualTo2Days()
{
    QCOMPARE(TimeConverter::millisecondsToDays(172800000), 2);
}


void TestTimeConverter::is2Days2Hours2MinutesEqualTo180120000Milliseconds()
{
    constexpr int days = 2;
    constexpr int hours = 2;
    constexpr int minutes = 2;

    QCOMPARE(TimeConverter::toMilliseconds(days, hours, minutes), 180120000);
}


void TestTimeConverter::is180120000MillisecondsConvertedToCorrectText()
{
    QCOMPARE(TimeConverter::timeToString(180120000), QString("2 days 2 hours 2 minutes"));
}

