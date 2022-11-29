#include "sizeconverter.h"


int SizeConverter::bytesToMegabytes(int bytes)
{
    return bytes / 1000000;
}

int SizeConverter::megabytesToBytes(int megabytes)
{
    return megabytes * 1000000;
}
