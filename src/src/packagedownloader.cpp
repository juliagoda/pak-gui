#include "packagedownloader.h"

#include "packageinputwindow.h"
#include "choicewindow.h"


PackageDownloader::PackageDownloader() :
    next_window(nullptr)
{
   // ...
}


QPointer<DownloaderWindow> &PackageDownloader::setNext(QPointer<DownloaderWindow>& new_window)
{
    this->next_window = new_window;
    return this->next_window;
}


void PackageDownloader::handle()
{
    if (this->next_window)
        this->next_window->handle();
}


PackageInput::PackageInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser) :
    PackageDownloader(),
    package_input_window(nullptr),
    download_command_parser(new_download_command_parser)
{
   // ...
}


void PackageInput::handle()
{
    package_input_window = new PackageInputWindow();
    connect(package_input_window.data(), &PackageInputWindow::packageNameInserted,
            [this](const QString& new_package_name)
    {
        download_command_parser->updatePackageName(new_package_name);
        PackageDownloader::handle();
    });

    connect(package_input_window.data(), &PackageInputWindow::cancelled,
        [this]()
        {
            download_command_parser->stop();
            package_input_window->close();
        });

    package_input_window->show();
}


void PackageInput::closeWindow()
{
    if (!package_input_window.isNull())
        package_input_window->close();
}


PathsChoiceInput::PathsChoiceInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser) :
    PackageDownloader(),
    download_command_parser(new_download_command_parser)
{
   // ...
}


void PathsChoiceInput::handle()
{
    QPointer<ChoiceWindow> choice_window = new ChoiceWindow(i18n("Choose path for package save"));
    connect(download_command_parser.get(), &DownloadCommandParser::continuePathsRetrieve, choice_window,
            QOverload<QString&>::of(&ChoiceWindow::fillComboBox));
    download_command_parser->start();
    connect(choice_window.data(), QOverload<int>::of(&ChoiceWindow::choiceDefined), [this](int new_index)
    {
        download_command_parser->inputAnswer(QString::number(new_index));
        download_command_parser->updateDirectoryChoice(new_index);
        PackageDownloader::handle();
    });

    connect(choice_window.data(), &ChoiceWindow::cancelled,
        [this, choice_window]()
        {
            download_command_parser->stop();
            choice_window->close();
        });

    choice_window->show();
}


ReposChoiceInput::ReposChoiceInput(QSharedPointer<DownloadCommandParser> &new_download_command_parser) :
    PackageDownloader(),
    download_command_parser(new_download_command_parser)
{
  // ...
}


void ReposChoiceInput::handle()
{
    QPointer<ChoiceWindow> choice_window = new ChoiceWindow(i18n("Choose repo for package download"));
    connect(download_command_parser.get(), &DownloadCommandParser::continueReposRetrieve, choice_window,
            QOverload<QString&>::of(&ChoiceWindow::fillComboBox));
    connect(choice_window.data(), QOverload<int>::of(&ChoiceWindow::choiceDefined), [this](int new_index)
    {
        emit acceptedChoice();
        download_command_parser->inputAnswer(QString::number(new_index));
    });

    connect(choice_window.data(), &ChoiceWindow::cancelled,
        [this, choice_window]()
        {
            download_command_parser->stop();
            choice_window->close();
        });

    choice_window->show();
}
