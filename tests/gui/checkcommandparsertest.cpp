 #include "checkcommandparsertest.h"


MockCheckCommandParser::MockCheckCommandParser() :
    CheckCommandParser()
{

}


QString MockCheckCommandParser::generatePakCheckResults()
{
    return QString(":: System\n"
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
                   "...\n");
}


bool MockCheckCommandParser::finishProcessBeforeEnd(bool starts_from_double_colon, const QString& current_source_line)
{
    return (starts_from_double_colon && QString::compare(current_source_line, "Unmerged pacnew/pacsave files") == 0);
}



TestCheckCommandParser::TestCheckCommandParser(QObject* parent) :
    QObject(parent),
    check_command_parser()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestCheckCommandParser::cleanup()
{

}
