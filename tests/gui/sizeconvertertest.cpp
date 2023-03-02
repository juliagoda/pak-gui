#include "sizeconvertertest.h"

#include "sizeconverter.h"


TestSizeConverter::TestSizeConverter(QObject* parent) :
    QObject{parent}
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestSizeConverter::is2000000BytesEqualTo2Megabytes()
{
    QCOMPARE(SizeConverter::bytesToMegabytes(2000000), 2);
}


void TestSizeConverter::is2MegabytesEqualTo2000000Bytes()
{
    QCOMPARE(SizeConverter::megabytesToBytes(2), 2000000);
}
