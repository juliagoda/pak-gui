 #include "packagesearchtest.h"



MockPackageSearch::MockPackageSearch() :
    PackageSearch()
{
  // ...
}



MockPackageSearchInput::MockPackageSearchInput(QSharedPointer<InstallCommandParser>& new_install_command_parser) :
    PackageSearchInput(new_install_command_parser)
{
  // ...
}




MockSearchResultsList::MockSearchResultsList(QSharedPointer<InstallCommandParser>& new_install_command_parser,
                                             QSharedPointer<Process>& new_process) :
    SearchResultsList(new_install_command_parser, new_process)
{
  // ...
}



TestPackageSearch::TestPackageSearch(QObject* parent) :
    QObject(parent),
    package_search(),
    package_search_input(install_command_parser),
    search_results_list(install_command_parser,
                        process)
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestPackageSearch::cleanup()
{
  // ...
}