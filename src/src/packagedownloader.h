#pragma once

#include "downloadcommandparser.h"

#include <QString>
#include <QPointer>
#include <QSharedPointer>
#include <QMessageBox>


class PackageInputWindow;

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
    PackageDownloader();

    QPointer<DownloaderWindow>& setNext(QPointer<DownloaderWindow>& new_window) override;
    void handle() override;
};


class PackageInput : public PackageDownloader
{
    Q_OBJECT

 public:
    PackageInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser);

    void handle() override;

 public slots:
    void closeWindow();

 private:
    QPointer<PackageInputWindow> package_input_window;
    QSharedPointer<DownloadCommandParser> download_command_parser;
};


class PathsChoiceInput : public PackageDownloader
{
    Q_OBJECT

 public:
    PathsChoiceInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser);

    void handle() override;

 private:
    QSharedPointer<DownloadCommandParser> download_command_parser;
};


class ReposChoiceInput : public PackageDownloader
{
    Q_OBJECT

 public:
    ReposChoiceInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser);

    void handle() override;

 signals:
    void acceptedChoice();

 private:
    QSharedPointer<DownloadCommandParser> download_command_parser;
};
