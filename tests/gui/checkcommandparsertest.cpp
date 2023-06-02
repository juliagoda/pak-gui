#include "checkcommandparsertest.h"

#include <QHash>


QString MockCheckCommandParser::generatePakCheckResults()
{
    return QString{":: Latest Arch Linux news: 2\n"
                   "...\n"
                   ":: System\n"
                   "Checking...\n"
                   "\n"
                   "Packages to update:\n"
                   "acl                             2.3.1-2.1 => 2.3.1-3.1\n"
                   "akonadi                         22.12.1-2.1 => 22.12.2-1.1\n"
                   ":: AUR\n"
                   "auracle-git (AUR) is not installed\n"
                   "\n"
                   ":: POLAUR\n"
                   "Checking...\n"
                   "\n"
                   "Packages to update:\n"
                   "repo-refreshed/konsole          22.12.1-1.1 => 22.12.2-1.4\n"
                   "\n"
                   ":: Unmerged pacnew/pacsave files\n"
                   "\n"
                   "...\n"};
}


TestCheckCommandParser::TestCheckCommandParser(QObject* parent) :
    QObject{parent},
    check_command_parser()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestCheckCommandParser::retrievedPackagesMapCountIsEqualToThree()
{
    auto results_map = check_command_parser.retrieveInfoMap();
    QCOMPARE(results_map.count(), 3);
}


void TestCheckCommandParser::retrievedPackagesMapContainsAclPackagesFromRepo()
{
   auto results_map = check_command_parser.retrieveInfoMap();
   QCOMPARE(results_map.value("acl 2.3.1-2.1 => 2.3.1-3.1"), Package::Source::Repo);
}


void TestCheckCommandParser::retrievedPackagesMapContainsKonsolePackageFromPolaur()
{
   auto results_map = check_command_parser.retrieveInfoMap();
   QCOMPARE(results_map.value("repo-refreshed/konsole 22.12.1-1.1 => 22.12.2-1.4"), Package::Source::POLAUR);
}
