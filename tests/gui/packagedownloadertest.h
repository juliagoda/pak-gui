#pragma once

#include "packagedownloader.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockPackageDownloader : public PackageDownloader
{
    Q_OBJECT

public:
    explicit MockPackageDownloader();
    friend class TestPackageDownloader;
};




class MockAutomaticInstallation : public AutomaticInstallation
{
    Q_OBJECT

public:
    explicit MockAutomaticInstallation(QSharedPointer<DownloadCommandParser>& new_download_command_parser,
                                       QWidget* new_parent);
    friend class TestPackageDownloader;

    QMessageBox::StandardButton chooseDownloadOption() override;
};




class MockPackageInput : public PackageInput
{
    Q_OBJECT

public:
    explicit MockPackageInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser);
    friend class TestPackageDownloader;
};





class MockPathsChoiceInput : public PathsChoiceInput
{
    Q_OBJECT

public:
    explicit MockPathsChoiceInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser);
    friend class TestPackageDownloader;
};




class MockReposChoiceInput : public ReposChoiceInput
{
    Q_OBJECT

public:
    explicit MockReposChoiceInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser);
    friend class TestPackageDownloader;
};




class TestPackageDownloader : public QObject
{
    Q_OBJECT

public:
    TestPackageDownloader(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockPackageDownloader package_downloader;
    MockAutomaticInstallation automatic_installation;
    MockPackageInput package_input;
    MockPathsChoiceInput paths_choice_input;
    MockReposChoiceInput repos_choice_input;
    QSharedPointer<DownloadCommandParser> download_command_parser = QSharedPointer<DownloadCommandParser>(nullptr);
};
