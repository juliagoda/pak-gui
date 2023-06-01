#include "previewdesigntest.h"


TestPreviewDesign::TestPreviewDesign(QObject* parent) :
    QObject(parent),
    preview_design()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestPreviewDesign::cleanup()
{
   // ...
}
