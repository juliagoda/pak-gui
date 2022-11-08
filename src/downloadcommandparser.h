#pragma once

#include "commandparser.h"

#include <QProcess>
#include <QScopedPointer>
#include <QString>

class DownloadCommandParser : public CommandParser
{
public:
    DownloadCommandParser(const QString& new_package_name);

    void updatePackageName(const QString& new_package_name);
    void updateParameter(const QString& new_parameter);
    QStringList getPaths();
    QStringList retrieveInfo() override;
    void inputAnswer(const QString& new_answer);

private:
    bool validate();

    QScopedPointer<QProcess> pak_download;
    QString package_name;
    QString command;
};

