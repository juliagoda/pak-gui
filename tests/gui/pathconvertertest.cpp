#include "pathconvertertest.h"

#include "pathconverter.h"


TestPathConverter::TestPathConverter(QObject* parent) :
    QObject{parent}
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestPathConverter::isRelativePathConvertedToAbsolutePath()
{
    const QRegExp regex{"/home/\\w+/path/example"};
    const QString path{"~/path/example"};

    QVERIFY(regex.exactMatch(PathConverter::toAbsolutePath(path)));
}


void TestPathConverter::isAbsolutePathTheSameAfterConversion()
{
    const QString path{"/home/someone/path/example"};

    QCOMPARE(PathConverter::toAbsolutePath(path), QString("/home/someone/path/example"));
}


void TestPathConverter::hasFullConfigPathCorrectForm()
{
   QCOMPARE(PathConverter::fullConfigPath(), QString("~/.config/pak-gui/logs.txt"));
}
