#include "packagesearch.h"

#include "outputfilter.h"
#include "packageinputwindow.h"
#include "choicewindow.h"
#include "searchallcommandparser.h"


PackageSearch::PackageSearch() :
    next_window(nullptr)
{
    // ...
}


QPointer<SearchWindow>& PackageSearch::setNext(QPointer<SearchWindow>& new_window)
{
    this->next_window = new_window;
    return this->next_window;
}


void PackageSearch::handle()
{
    if (this->next_window)
        this->next_window->handle();
}



PackageSearchInput::PackageSearchInput(QSharedPointer<InstallCommandParser>& new_install_command_parser) :
    PackageSearch(),
    install_command_parser(new_install_command_parser),
    package_input_window(nullptr)
{
    // ...
}


void PackageSearchInput::handle()
{
    package_input_window = new PackageInputWindow();
    connect(package_input_window.data(), &PackageInputWindow::packageNameInserted,
            [this](const QString& new_package_name)
    {
        install_command_parser->updatePackageName(new_package_name);
        PackageSearch::handle();
    });

    package_input_window->show();
}


void PackageSearchInput::closeWindow()
{
    if (!package_input_window.isNull())
        package_input_window->close();
}


SearchResultsList::SearchResultsList(QSharedPointer<InstallCommandParser>& new_install_command_parser,
                                     QSharedPointer<Process>& new_process,
                                     uint packages_to_update_count) :
    PackageSearch(),
    install_command_parser(new_install_command_parser),
    process(new_process),
    packages_to_update(packages_to_update_count)
{
   // ...
}


void SearchResultsList::handle()
{
    QPointer<SearchAllCommandParser> search_all_command_parser(new SearchAllCommandParser(install_command_parser->getPackageName()));

    QPointer<ChoiceWindow> choice_window = new ChoiceWindow(tr("Choose package"));
    connect(search_all_command_parser, &SearchAllCommandParser::searchEnded, choice_window,
            QOverload<QStringList>::of(&ChoiceWindow::fillComboBox));
    search_all_command_parser->retrieveInfo();
    connect(choice_window, QOverload<QString>::of(&ChoiceWindow::choiceDefined), [this](QString chosen_package)
    {
        emit acceptedChoice();
        install_command_parser->updateTask(OutputFilter::getSourceFromSearchLine(chosen_package));
        install_command_parser->updatePackageName(OutputFilter::getPackageFromSearchLine(chosen_package));
        install_command_parser->start(process, packages_to_update);
    });

    choice_window->show();
}
