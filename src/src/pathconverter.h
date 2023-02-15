#pragma once

#include <QString>
#include <QDir>

class PathConverter
{
public:
    virtual ~PathConverter() = default;

    static QString toAbsolutePath(const QString &new_path);
    static QString fullConfigPath();
};

