#include "statisticswindowtesttest.h"



MockStatisticsWindow::MockStatisticsWindow(const QMap<QString, uint>& new_statistics_map,
                                           QWidget* parent) :
    Statistics(new_statistics_map, parent)
{
  // ...
}



TestStatisticsWindow::TestStatisticsWindow(QObject* parent) :
    QObject(parent),
    statistics_window(map, new QWidget)
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestStatisticsWindow::cleanup()
{
  // ...
}
