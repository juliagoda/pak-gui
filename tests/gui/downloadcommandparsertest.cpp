 #include "downloadcommandparsertest.h"


MockDownloadCommandParser::MockDownloadCommandParser(const QString& new_package_name, QWidget* new_parent) :
    DownloadCommandParser(new_package_name, new_parent)
{
    // ...
}


void MockDownloadCommandParser::start()
{
    // ...
}


void MockDownloadCommandParser::inputAnswer(const QString &new_answer)
{
    // ...
}


void MockDownloadCommandParser::showWarningWhenNameEmpty()
{
    // ...
}


void MockDownloadCommandParser::connectSignals()
{
    // ...
}


bool MockDownloadCommandParser::validateFinishedOutput(int exit_code)
{
    Q_UNUSED(exit_code)
    return isPackageAlreadyDownloaded();
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
