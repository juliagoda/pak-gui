#include "packagedownloader.h"

#include "packageinputwindow.h"
#include "choicewindow.h"


PackageDownloader::PackageDownloader() :
    next_window(nullptr)
{

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



AutomaticInstallation::AutomaticInstallation(QSharedPointer<DownloadCommandParser>& new_download_command_parser,
                                             QWidget* new_parent) :
    PackageDownloader(),
    download_command_parser(new_download_command_parser),
    parent(new_parent)
{

}


void AutomaticInstallation::handle()
{
    download_command_parser->updateParameter(chooseDownloadOption() == QMessageBox::Yes ? QString("pak -GB") : QString("pak -G"));
    PackageDownloader::handle();
}


QMessageBox::StandardButton AutomaticInstallation::chooseDownloadOption()
{
    return static_cast<QMessageBox::StandardButton>(QMessageBox::information(parent, tr("Downloader's option"),
                                                                             tr("Do you want to install chosen package automatically after download?"),
                                                                             QMessageBox::Yes | QMessageBox::No));
}



PackageInput::PackageInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser) :
    PackageDownloader(),
    download_command_parser(new_download_command_parser)
{

}


void PackageInput::handle()
{
    QPointer<PackageInputWindow> package_input_window = new PackageInputWindow();
    connect(package_input_window.data(), &PackageInputWindow::packageNameInserted,
            [this](const QString& new_package_name)
    {
        download_command_parser->updatePackageName(new_package_name);
        PackageDownloader::handle();
    });

    package_input_window->show();
}




PathsChoiceInput::PathsChoiceInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser) :
    PackageDownloader(),
    download_command_parser(new_download_command_parser)
{

}


void PathsChoiceInput::handle()
{
    QPointer<ChoiceWindow> choice_window = new ChoiceWindow(tr("Choose path for package save"));
    connect(download_command_parser.get(), &DownloadCommandParser::continuePathsRetrieve, choice_window,
            QOverload<QString&>::of(&ChoiceWindow::fillComboBox));
    download_command_parser->start();
    connect(choice_window.data(), QOverload<int>::of(&ChoiceWindow::choiceDefined), [this](int new_index)
    {
        download_command_parser->inputAnswer(QString::number(new_index));
        PackageDownloader::handle();
    });

    choice_window->show();
}




ReposChoiceInput::ReposChoiceInput(QSharedPointer<DownloadCommandParser> &new_download_command_parser) :
    PackageDownloader(),
    download_command_parser(new_download_command_parser)
{

}


void ReposChoiceInput::handle()
{
    QPointer<ChoiceWindow> choice_window = new ChoiceWindow(tr("Choose repo for package download"));
    connect(download_command_parser.get(), &DownloadCommandParser::continueReposRetrieve, choice_window,
            QOverload<QString&>::of(&ChoiceWindow::fillComboBox));
    connect(choice_window.data(), QOverload<int>::of(&ChoiceWindow::choiceDefined), [this](int new_index)
    {
        download_command_parser->inputAnswer(QString::number(new_index));
    });

    choice_window->show();
}
