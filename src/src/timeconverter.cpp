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
