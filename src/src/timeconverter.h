#pragma once

#include <QString>

class TimeConverter
{
public:
    virtual ~TimeConverter() = default;
    static int minutesToMilliseconds(int minutes);
    static int millisecondsToMinutes(int milliseconds);
    static int hoursToMilliseconds(int hours);
    static int millisecondsToHours(int milliseconds);
    static int daysToMilliseconds(int days);
    static int millisecondsToDays(int milliseconds);
    static int toMilliseconds(int days, int hours, int minutes);
    static QString timeToString(int milliseconds);
};

