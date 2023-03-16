#include "qicommandparsertest.h"

#include "packagescolumnfixtures.h"


QString MockQiCommandParser::generateResult()
{
    QString gimp = package_content_gimp;
    return gimp.append("\n").append(package_content_a52dec);
}


TestQiCommandParser::TestQiCommandParser(QObject* parent) :
    QObject(parent),
    qi_command_parser()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestQiCommandParser::initTestCase_data()
{
   QTest::addColumn<QStringList>("command_parser_results");
   QTest::newRow("qi") << qi_command_parser.retrieveInfo();
}


void TestQiCommandParser::isListContainingTwoPackages()
{
   QFETCH_GLOBAL(QStringList, command_parser_results);
   QCOMPARE(command_parser_results.count(), 2);
}


void TestQiCommandParser::isListContainingPackagesWithCorrectContent()
{
    QFETCH_GLOBAL(QStringList, command_parser_results);
    QCOMPARE(QStringLiteral("%1\n").arg(command_parser_results.constFirst().data()), package_content_gimp);
    QCOMPARE(command_parser_results.constLast().data(), package_content_a52dec);
}
