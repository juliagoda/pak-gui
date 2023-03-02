#pragma once

#include <QString>
#include <QDir>

class PathConverter
{
public:
    static QString toAbsolutePath(const QString &new_path);
    static QString fullConfigPath();
};

