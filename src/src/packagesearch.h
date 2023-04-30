#pragma once

#include "installcommandparser.h"

#include "process.h"

#include <QString>
#include <QPointer>
#include <QSharedPointer>
#include <QMessageBox>
#include <QProcess>


class SearchWindow : public QObject
{
    Q_OBJECT

public:
    virtual QPointer<SearchWindow>& setNext(QPointer<SearchWindow>& new_window) = 0;
    virtual ~SearchWindow() override = default;
    virtual void handle() = 0;
};


class PackageSearch : public SearchWindow
{
    Q_OBJECT

private:
    QPointer<SearchWindow> next_window;

public:
    PackageSearch();

    QPointer<SearchWindow>& setNext(QPointer<SearchWindow>& new_window) override;
    void handle() override;
};


class PackageSearchInput : public PackageSearch
{
    Q_OBJECT

public:
    PackageSearchInput(QSharedPointer<InstallCommandParser>& new_install_command_parser);

    void handle() override;

private:
    QSharedPointer<InstallCommandParser> install_command_parser;
};


class SearchResultsList : public PackageSearch
{
    Q_OBJECT

public:
    SearchResultsList(QSharedPointer<InstallCommandParser>& new_install_command_parser,
                      QSharedPointer<Process>& new_process,
                      uint packages_to_update_count);

    void handle() override;

private:
    QSharedPointer<InstallCommandParser> install_command_parser;
    QSharedPointer<Process> process;
    uint packages_to_update;
};
