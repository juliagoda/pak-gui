#include "statisticswindowtesttest.h"



MockStatisticsWindow::MockStatisticsWindow(const QMap<QString, uint>& new_statistics_map,
                                           QWidget* parent = nullptr) :
    Statistics(new_statistics_map, parent)
{
  // ...
}



TestStatisticsWindow::TestStatisticsWindow(QObject* parent) :
    QObject(parent),
    statistics_window(map)
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestStatisticsWindow::cleanup()
{
  // ...
}
