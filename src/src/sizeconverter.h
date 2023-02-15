#pragma once


class SizeConverter
{
public:
    virtual ~SizeConverter() = default;

    static int bytesToMegabytes(int bytes);
    static int megabytesToBytes(int megabytes);
};

