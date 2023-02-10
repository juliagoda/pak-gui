 #include "downloadcommandparsertest.h"


MockDownloadCommandParser::MockDownloadCommandParser(const QString& new_package_name, QWidget* new_parent) :
    DownloadCommandParser(new_package_name, new_parent)
{
   // ...
}



TestDownloadCommandParser::TestDownloadCommandParser(QObject* parent) :
    QObject(parent),
    download_command_parser(QString(""), new QWidget)
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestDownloadCommandParser::cleanup()
{
   // ...
}
