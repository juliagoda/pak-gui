#pragma once

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
    PackageDownloader();

    QPointer<DownloaderWindow>& setNext(QPointer<DownloaderWindow>& new_window) override;
    void handle() override;
};


class AutomaticInstallation : public PackageDownloader
{
    Q_OBJECT

public:
    AutomaticInstallation(QSharedPointer<DownloadCommandParser>& new_download_command_parser,
                          QWidget* new_parent);

    void handle() override;

private:
    QSharedPointer<DownloadCommandParser> download_command_parser;
    QWidget* parent;
};


class PackageInput : public PackageDownloader
{
    Q_OBJECT

public:
    PackageInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser);

    void handle() override;

private:
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

private:
    QSharedPointer<DownloadCommandParser> download_command_parser;
};
