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

