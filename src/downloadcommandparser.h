#pragma once

#include "commandparser.h"
#include "qobjectdefs.h"

#include <QProcess>
#include <QScopedPointer>
#include <QString>

class DownloadCommandParser : public CommandParser
{
    Q_OBJECT
public:
    DownloadCommandParser(const QString& new_package_name);

    void updatePackageName(const QString& new_package_name);
    void updateParameter(const QString& new_parameter);
    void start();
    QStringList retrieveInfo() override;
    void inputAnswer(const QString& new_answer);

Q_SIGNALS:
    void continuePathsRetrieve(QString& output);
    void continueReposRetrieve(QString& output);

private:
    bool validate();

    QScopedPointer<QProcess> pak_download;
    QString package_name;
    QString command;
    QString result_output;
};

