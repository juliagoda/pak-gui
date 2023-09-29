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

#include "loggertest.h"


TestLogger::TestLogger(QObject* parent) :
    QObject{parent}
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestLogger::writeSectionToFileMethodHasCorrectTextFormat()
{
    logger.writeSectionToFile(write_operation);

    QString section_text{QVariant::fromValue(write_operation).toString()};
    QString expected_result{QDateTime::currentDateTime().toLocalTime().toString() +
                           QString("\n\n\n---------------[").append(section_text.toUpper()).append(QString("]---------------")) +
                           QString("\n\n")};

    QCOMPARE(logger.streamTextResult(), expected_result);
}


void TestLogger::writeLineToFileMethodHasCorrectTextFormat()
{
    logger.writeLineToFile(text);
    QString expected_result{QString("text\n\n")};

    QCOMPARE(logger.streamTextResult(), expected_result);
}


void TestLogger::writeToFileMethodHasCorrectTextFormat()
{
    logger.writeToFile(text, write_operation);

    QString section_text{QVariant::fromValue(write_operation).toString()};
    QString expected_result{QDateTime::currentDateTime().toLocalTime().toString() +
                QString("\n\n\n---------------[").append(section_text.toUpper()).append(QString("]---------------")) +
                QString("\n\ntext") +
                QString("\n\n////////////////////////////////////////////////////////////") +
                QString("\n\n\n\n")};

    QCOMPARE(logger.streamTextResult(), expected_result);
}


void TestLogger::logIntoFileMethodHasCorrectTextFormat()
{
    QString section_text{QVariant::fromValue(write_operation).toString()};
    logger.logIntoFile(section_text, text);

    QString local_time{QDateTime::currentDateTime().toLocalTime().toString()};
    QString expected_result{QString(" [" + section_text + "]  text  (" + local_time + ")\n")};

    QCOMPARE(logger.streamTextResult(), expected_result);
}


void TestLogger::loggerPublicInstanceIsAlwaysTheSame()
{
    auto instance = logger.logger();

    QCOMPARE(instance, logger.logger());
}


void TestLogger::cleanup()
{
    logger.clearStreamText();
}
