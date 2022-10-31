#pragma once

#include "commandparser.h"

#include <QProcess>
#include <QScopedPointer>
#include <QString>

class DownloadCommandParser : public CommandParser
{
public:
    DownloadCommandParser(const QString& new_package_name, bool new_is_built);

    void updatePackageName(const QString& new_package_name);
    QStringList getPaths();
    QStringList retrieveInfo() override;
    void inputAnswer(const QString& new_answer);

private:
    QScopedPointer<QProcess> pak_download;
    QString package_name;
    QString parameter;
};

