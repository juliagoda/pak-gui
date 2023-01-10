#include "timeconverter.h"


int TimeConverter::minutesToMilliseconds(int minutes)
{
    return minutes * 60000;
}


int TimeConverter::hoursToMilliseconds(int hours)
{
    return hours * 3600000;
}


int TimeConverter::daysToMilliseconds(int days)
{
    return days * 86400000;
}


int TimeConverter::toMilliseconds(int days, int hours, int minutes)
{
    return daysToMilliseconds(days) + hoursToMilliseconds(hours) + minutesToMilliseconds(minutes);
}


int TimeConverter::millisecondsToMinutes(int milliseconds)
{
    return milliseconds / 60000;
}


int TimeConverter::millisecondsToHours(int milliseconds)
{
    return milliseconds / 3600000;
}


int TimeConverter::millisecondsToDays(int milliseconds)
{
    return milliseconds / 86400000;
}


QString TimeConverter::timeToString(int milliseconds)
{
    int days = millisecondsToDays(milliseconds);
    int hours = millisecondsToHours(milliseconds - daysToMilliseconds(days));
    int minutes = millisecondsToMinutes(milliseconds - daysToMilliseconds(days) - hoursToMilliseconds(hours));
    return QString("%1 days %2 hours %3 minutes").arg(days).arg(hours).arg(minutes);
}
