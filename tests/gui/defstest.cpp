#include "defstest.h"


TestDefs::TestDefs(QObject* parent) :
    QObject(parent)
{

}

void TestDefs::packageQiNameLineIsEqualToZero()
{
   QCOMPARE(PACKAGE_QI_NAME_LINE, 0);
}


void TestDefs::cleanup()
{

}
