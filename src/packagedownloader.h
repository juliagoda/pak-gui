#pragma once

#include "packageinputwindow.h"
#include "choicewindow.h"
#include "downloadcommandparser.h"

#include <QString>
#include <QPointer>
#include <QSharedPointer>
#include <QMessageBox>


class DownloaderWindow : public QObject
{
    Q_OBJECT

public:
    virtual QPointer<DownloaderWindow>& setNext(QPointer<DownloaderWindow>& new_window) = 0;
    virtual ~DownloaderWindow() = default;
    virtual void handle() = 0;
};


class PackageDownloader : public DownloaderWindow
{
    Q_OBJECT

private:
    QPointer<DownloaderWindow> next_window;

public:
    PackageDownloader() :
        next_window(nullptr)
    {}

    QPointer<DownloaderWindow>& setNext(QPointer<DownloaderWindow>& new_window) override
    {
        this->next_window = new_window;
        return this->next_window;
    }

    void handle() override
    {
        if (this->next_window)
            this->next_window->handle();
    }
};


class AutomaticInstallation : public PackageDownloader
{
    Q_OBJECT

public:
    AutomaticInstallation(QPointer<DownloadCommandParser>& new_download_command_parser) :
        PackageDownloader(),
        download_command_parser(new_download_command_parser)
    {}

    void handle() override
    {
        bool answer = true;
        int answer_gui = QMessageBox::information(new QWidget, tr("Downloader's option"),
                                                  tr("Do you want to install chosen package automatically after download?"),
                                                  QMessageBox::Yes | QMessageBox::No);

        if (static_cast<QMessageBox::StandardButton>(answer_gui) == QMessageBox::No)
            answer = false;

        download_command_parser->updateParameter(answer ? QString("pak -GB") : QString("pak -G"));
        PackageDownloader::handle();
    }

private:
    QPointer<DownloadCommandParser> download_command_parser;
};


class PackageInput : public PackageDownloader
{
    Q_OBJECT

public:
    PackageInput(QPointer<DownloadCommandParser>& new_download_command_parser) :
        PackageDownloader(),
        download_command_parser(new_download_command_parser)
    {}

    void handle() override
    {
        QPointer<PackageInputWindow> package_input_window = new PackageInputWindow();
        connect(package_input_window.data(), &PackageInputWindow::packageNameInserted, [this, &package_input_window](const QString& new_package_name)
        {
            download_command_parser->updatePackageName(new_package_name);
            PackageDownloader::handle();
        });

        package_input_window->show();
    }

private:
    QPointer<DownloadCommandParser> download_command_parser;
};


class PathsChoiceInput : public PackageDownloader
{
    Q_OBJECT

public:
    PathsChoiceInput(QPointer<DownloadCommandParser>& new_download_command_parser) :
        PackageDownloader(),
        download_command_parser(new_download_command_parser)
    {}

    void handle() override
    {
        QPointer<ChoiceWindow> choice_window = new ChoiceWindow(tr("Choose path for package save"));
        connect(download_command_parser, &DownloadCommandParser::continuePathsRetrieve, choice_window, &ChoiceWindow::fillComboBox);
        download_command_parser->start();
        connect(choice_window.data(), &ChoiceWindow::choiceDefined, [this, &choice_window](int new_index)
        {
            download_command_parser->inputAnswer(QString::number(new_index));
            PackageDownloader::handle();
        });

        choice_window->show();
    }

private:
    QPointer<DownloadCommandParser> download_command_parser;
};


class ReposChoiceInput : public PackageDownloader
{
    Q_OBJECT

public:
    ReposChoiceInput(QPointer<DownloadCommandParser>& new_download_command_parser) :
        PackageDownloader(),
        download_command_parser(new_download_command_parser)
    {}

    void handle() override
    {
        QPointer<ChoiceWindow> choice_window = new ChoiceWindow(tr("Choose repo for package download"));
        connect(download_command_parser, &DownloadCommandParser::continueReposRetrieve, choice_window, &ChoiceWindow::fillComboBox);
        connect(choice_window.data(), &ChoiceWindow::choiceDefined, [this, &choice_window](int new_index)
        {
            download_command_parser->inputAnswer(QString::number(new_index));
        });

        choice_window->show();
    }

private:
    QPointer<DownloadCommandParser> download_command_parser;
};
