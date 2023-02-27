#include "checkpackagetest.h"


TestCheckPackage::TestCheckPackage(QObject* parent) :
    QObject{parent},
    check_package{"binutils 2.40-1.1 => 2.40-2.1",
                  Package::Source::Repo}
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestCheckPackage::isItemCheckable()
{
    QCOMPARE(check_package.flags(), Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
}


void TestCheckPackage::isItemNotCheckedByDefault()
{
    QCOMPARE(check_package.checkState(), Qt::Unchecked);
}


void TestCheckPackage::isItemNameEqualToBinutils()
{
    QCOMPARE(check_package.getName(), QString("binutils"));
}


void TestCheckPackage::isItemVersionCorrectlyVisible()
{
    QCOMPARE(check_package.getVersion(), QString("2.40-1.1 => 2.40-2.1"));
}


void TestCheckPackage::isSourceEqualToRepo()
{
    QCOMPARE(check_package.getSource(), Package::Source::Repo);
}
