#include "progressviewtest.h"


MockProgressView::MockProgressView(QDialog* parent) :
    ProgressView(parent)
{
   // ...
}



TestProgressView::TestProgressView(QObject* parent) :
    QObject(parent),
    progress_view(new QWidget)
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestProgressView::cleanup()
{
   // ...
}
