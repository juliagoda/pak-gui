#pragma once

#include "packagesearch.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockPackageSearch : public PackageSearch
{
    Q_OBJECT

public:
    explicit MockPackageSearch();
    friend class TestPackageSearch;
};




class MockPackageSearchInput : public PackageSearchInput
{
    Q_OBJECT

public:
    explicit MockPackageSearchInput(QSharedPointer<InstallCommandParser>& new_install_command_parser);
    friend class TestPackageSearch;
};




class MockSearchResultsList : public SearchResultsList
{
    Q_OBJECT

public:
    explicit MockSearchResultsList(QSharedPointer<InstallCommandParser>& new_install_command_parser,
                                   QSharedPointer<Process>& new_process);
    friend class TestPackageSearch;
};




class TestPackageSearch : public QObject
{
    Q_OBJECT

public:
    TestPackageSearch(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockPackageSearch package_search;
    MockPackageSearchInput package_search_input;
    MockSearchResultsList search_results_list;
    QSharedPointer<InstallCommandParser> install_command_parser = QSharedPointer<InstallCommandParser>(nullptr);
    QSharedPointer<Process> process = QSharedPointer<Process>(nullptr);
};
