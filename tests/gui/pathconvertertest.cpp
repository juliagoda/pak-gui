 #include "pathconvertertest.h"


TestPathConverter::TestPathConverter(QObject* parent) :
    QObject(parent),
    path_converter()
{
    QTestEventLoop::instance().enterLoop(1);
}


void TestPathConverter::cleanup()
{

}
