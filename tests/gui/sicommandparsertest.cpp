#include "sicommandparsertest.h"

#include "packagescolumnfixtures.h"



QString MockSiCommandParser::generateResult()
{
    QString a52dec = package_content_a52dec_si;
    return a52dec.append("\n").append(package_content_alsa_utils_si);
}


TestSiCommandParser::TestSiCommandParser(QObject* parent) :
    QObject(parent),
    si_command_parser()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestSiCommandParser::initTestCase_data()
{
    QTest::addColumn<QStringList>("command_parser_results");
    QTest::newRow("si") << si_command_parser.retrieveInfo();
}


void TestSiCommandParser::isListContainingTwoPackages()
{
    QFETCH_GLOBAL(QStringList, command_parser_results);
    QCOMPARE(command_parser_results.count(), 2);
}


void TestSiCommandParser::isListContainingPackagesWithCorrectContent()
{
    QFETCH_GLOBAL(QStringList, command_parser_results);
    QCOMPARE(QStringLiteral("%1\n").arg(command_parser_results.constFirst().data()), package_content_a52dec_si);
    QCOMPARE(command_parser_results.constLast().data(), package_content_alsa_utils_si);
}
