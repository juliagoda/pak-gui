 #include "packagedownloadertest.h"


MockPackageDownloader::MockPackageDownloader() :
    PackageDownloader()
{
  // ...
}



MockAutomaticInstallation::MockAutomaticInstallation(QSharedPointer<DownloadCommandParser>& new_download_command_parser,
                                                     QWidget* new_parent) :
    AutomaticInstallation(new_download_command_parser, new_parent)
{
  // ...
}



MockPackageInput::MockPackageInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser) :
    PackageInput(new_download_command_parser)
{
  // ...
}



MockPathsChoiceInput::MockPathsChoiceInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser) :
    PathsChoiceInput(new_download_command_parser)
{
  // ...
}



MockReposChoiceInput::MockReposChoiceInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser) :
    ReposChoiceInput(new_download_command_parser)
{
  // ...
}



TestPackageDownloader::TestPackageDownloader(QObject* parent) :
    QObject(parent),
    package_downloader(),
    automatic_installation(download_command_parser,
                           new QWidget),
    package_input(download_command_parser),
    paths_choice_input(download_command_parser),
    repos_choice_input(download_command_parser)

{
    QTestEventLoop::instance().enterLoop(1);
}


void TestPackageDownloader::cleanup()
{
  // ...
}
