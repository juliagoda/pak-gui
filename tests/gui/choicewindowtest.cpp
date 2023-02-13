#include "choicewindowtest.h"


MockChoiceWindow::MockChoiceWindow(const QString& new_title,
                                   QDialog* new_parent) :
    ChoiceWindow(new_title, new_parent)
{
   // ...
}



TestChoiceWindow::TestChoiceWindow(QObject* parent) :
    QObject(parent),
    choice_window(QString(""))
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestChoiceWindow::cleanup()
{
   // ...
}
