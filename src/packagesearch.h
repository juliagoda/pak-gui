#pragma once

#include "outputfilter.h"
#include "packageinputwindow.h"
#include "choicewindow.h"
#include "installcommandparser.h"
#include "searchallcommandparser.h"
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
    virtual ~SearchWindow() = default;
    virtual void handle() = 0;
};


class PackageSearch : public SearchWindow
{
    Q_OBJECT

private:
    QPointer<SearchWindow> next_window;

public:
    PackageSearch() :
        next_window(nullptr)
    {}

    QPointer<SearchWindow>& setNext(QPointer<SearchWindow>& new_window) override
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


class PackageSearchInput : public PackageSearch
{
    Q_OBJECT

public:
    PackageSearchInput(QSharedPointer<InstallCommandParser>& new_install_command_parser) :
        PackageSearch(),
        install_command_parser(new_install_command_parser)
    {}

    void handle() override
    {
        QPointer<PackageInputWindow> package_input_window = new PackageInputWindow();
        connect(package_input_window.data(), &PackageInputWindow::packageNameInserted, [this](const QString& new_package_name)
        {
            install_command_parser->updatePackageName(new_package_name);
            PackageSearch::handle();
        });

        package_input_window->show();
    }

private:
    QSharedPointer<InstallCommandParser> install_command_parser;
};


class SearchResultsList : public PackageSearch
{
    Q_OBJECT

public:
    SearchResultsList(QSharedPointer<InstallCommandParser>& new_install_command_parser, QSharedPointer<Process>& new_process) :
        PackageSearch(),
        install_command_parser(new_install_command_parser),
        process(new_process)
    {}

    void handle() override
    {
        QPointer<SearchAllCommandParser> search_all_command_parser(new SearchAllCommandParser(install_command_parser->getPackageName()));

        QPointer<ChoiceWindow> choice_window = new ChoiceWindow(tr("Choose package"));
        connect(search_all_command_parser, &SearchAllCommandParser::searchEnded, choice_window, QOverload<QStringList>::of(&ChoiceWindow::fillComboBox));
        search_all_command_parser->retrieveInfo();
        connect(choice_window, QOverload<QString>::of(&ChoiceWindow::choiceDefined), [this](QString chosen_package)
        {
            install_command_parser->updateTask(OutputFilter::getSourceFromSearchLine(chosen_package));
            install_command_parser->updatePackageName(OutputFilter::getPackageFromSearchLine(chosen_package));
            install_command_parser->start(process);
        });

        choice_window->show();
    }

private:
    QSharedPointer<InstallCommandParser> install_command_parser;
    QSharedPointer<Process> process;
};
