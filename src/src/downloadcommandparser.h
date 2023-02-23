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
    DownloadCommandParser(const QString& new_package_name, QWidget* new_parent);
    ~DownloadCommandParser() override = default;

    void updatePackageName(const QString& new_package_name);
    void updateParameter(const QString& new_parameter);
    virtual void start();
    QStringList retrieveInfo() override;
    virtual void inputAnswer(const QString& new_answer);

protected:
    virtual void showWarningWhenNameEmpty();
    virtual void connectSignals();
    void processReadLine(QString& line);
    bool isPackageAlreadyDownloaded();

Q_SIGNALS:
    void continuePathsRetrieve(QString& output);
    void continueReposRetrieve(QString& output);

protected Q_SLOTS:
    virtual bool validateFinishedOutput(int exit_code);

private:
    bool validate();

    QScopedPointer<QProcess> pak_download = QScopedPointer<QProcess>(nullptr);
    QString package_name;
    QString command = QString("pak -G");
    QString result_output;
    QStringList error_lines;
    QWidget* parent = nullptr;
};

