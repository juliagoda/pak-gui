#pragma once

#include "commandparser.h"
#include "qobjectdefs.h"

#include <QProcess>
#include <QScopedPointer>
#include <QString>
#include <QMap>

class DownloadCommandParser : public CommandParser
{
    Q_OBJECT
public:
    DownloadCommandParser(const QString& new_package_name, QWidget* new_parent);
    ~DownloadCommandParser() override = default;

    void updatePackageName(const QString& new_package_name);
    virtual void start();
    virtual void stop();
    QStringList retrieveInfo() override;
    virtual void inputAnswer(const QString& new_answer);
    void updateDirectoryChoice(int directory_no);

protected:
    virtual void showWarningWhenNameEmpty();
    virtual void connectSignals();
    void processReadLine(QString& line, int& directories_line_count);
    bool isPackageAlreadyDownloaded();

Q_SIGNALS:
    void continuePathsRetrieve(QString& output);
    void continueReposRetrieve(QString& output);

protected Q_SLOTS:
    virtual bool validateFinishedOutput(int exit_code);
    virtual void showDirectory(int exit_code);

private:
    bool validate();
    void fillDirectoriesMap(const QString& result);
    void addLineToDirectoriesMap(const QString& result);
    void processForDirectories(const QString& filtered_line, int& directories_line_count);
    void processForRepos();

    using DirectoryNo = int;
    using DirectoryPath = QString;

    QScopedPointer<QProcess> pak_download = QScopedPointer<QProcess>(nullptr);
    QString package_name;
    QString command = QString("pak -G");
    QString result_output;
    QStringList error_lines;
    QWidget* parent = nullptr;
    QMap<DirectoryNo, DirectoryPath> directories_map;
    int directory_no_choice = -1;
    bool isTerminated = false;
};

