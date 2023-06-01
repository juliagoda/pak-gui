#include "searchallcommandparsertest.h"


MockSearchAllCommandParser::MockSearchAllCommandParser(const QString& new_package_name) :
    SearchAllCommandParser(new_package_name)
{
    // ...
}


QStringList MockSearchAllCommandParser::retrieveInfo()
{
   return QStringList();
}


TestSearchAllCommandParser::TestSearchAllCommandParser(QObject* parent) :
    QObject(parent),
    search_all_command_parser(QString(""))
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestSearchAllCommandParser::cleanup()
{
   // ...
}
