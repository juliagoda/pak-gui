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
