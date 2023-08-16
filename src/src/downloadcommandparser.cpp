// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of CachyOS package manager based on "pak" application.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "downloadcommandparser.h"

#include "logger.h"

#include <KLocalizedString>
#include <QScopedPointer>
#include <QMessageBox>
#include <QProcess>
#include <QStringLiteral>
#include <QRegularExpression>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>
#include <QStringLiteral>
#include <QDesktopServices>


DownloadCommandParser::DownloadCommandParser(const QString& new_package_name,
                                             QWidget* new_parent) :
    package_name(new_package_name),
    parent(new_parent)
{
    connectSignals();
}


void DownloadCommandParser::connectSignals()
{
    int directories_line_count = 0;
    pak_download.reset(new QProcess);
    pak_download->setProcessChannelMode(QProcess::MergedChannels);

    if (pak_download.isNull())
        return;

    QObject::connect(this, &DownloadCommandParser::ended, this, [this]() { clearAfterExecution(pak_download); });
    QObject::connect(pak_download.get(), QOverload<int>::of(&QProcess::finished), [this]() { emit ended(); });
    QObject::connect(pak_download.get(), QOverload<int>::of(&QProcess::finished), this, &DownloadCommandParser::validateFinishedOutput);
    QObject::connect(pak_download.get(), QOverload<int>::of(&QProcess::finished), this, &DownloadCommandParser::showDirectory);
    QObject::connect(pak_download.get(), &QProcess::errorOccurred, [this]() {
        if (!isTerminated)
        Logger::logger()->logWarning(QStringLiteral("Error during download: %1").arg(pak_download->errorString()));
    });

    QObject::connect(pak_download.get(), &QProcess::readyReadStandardOutput, [this, directories_line_count]() mutable
    {
        while (pak_download.data()->canReadLine())
        {
            QString line = pak_download.data()->readLine();
            processReadLine(line, directories_line_count);
        }
    });
}


void DownloadCommandParser::processReadLine(QString& line, int& directories_line_count)
{
    auto filtered_line = output_filter->filteredOutput(line);
    Logger::logger()->writeLineToFile(filtered_line);
    result_output += filtered_line;

    static QRegularExpression errors_regex{"^([a-z]+:\\s+)(.*)"};
    QRegularExpressionMatch match = errors_regex.match(filtered_line);
    if (match.hasMatch())
        error_lines.append(match.captured(2));

    processForDirectories(filtered_line, directories_line_count);
    processForRepos();
}


bool DownloadCommandParser::isPackageAlreadyDownloaded()
{
    return result_output.contains("PKGBUILD");
}


void DownloadCommandParser::updatePackageName(const QString& new_package_name)
{
    package_name = new_package_name;
}


void DownloadCommandParser::start()
{
    if (!validate())
        Logger::logger()->logWarning("retrieving paths from download command parser is not possible");

    Logger::logger()->logInfo(QStringLiteral("Trying download package: %1 with command %2").arg(package_name, command.trimmed()));
    Logger::logger()->writeSectionToFile(Logger::WriteOperations::Download);
    pak_download->start("/bin/bash", QStringList() << "-c" << command + " " + package_name.trimmed());
    pak_download->waitForStarted();
    pak_download->waitForReadyRead();
}


void DownloadCommandParser::stop()
{
    Logger::logger()->logInfo(QStringLiteral("Stop of package download"));
    isTerminated = true;
    pak_download->terminate();
}


void DownloadCommandParser::inputAnswer(const QString& new_answer)
{
    if (pak_download->state() != QProcess::Running && !pak_download->isWritable())
    {
        Logger::logger()->logWarning("Download command parser process is not running. Answer input is not possible");
        return;
    }

    Logger::logger()->logInfo(QStringLiteral("Chosen option: %1").arg(new_answer));
    pak_download->write(new_answer.toLocal8Bit());
    pak_download->waitForReadyRead();
}


void DownloadCommandParser::updateDirectoryChoice(int directory_no)
{
    directory_no_choice = directory_no;
}


bool DownloadCommandParser::validate()
{
    if (package_name.isEmpty())
    {
        showWarningWhenNameEmpty();
        return false;
    }

    return true;
}


void DownloadCommandParser::fillDirectoriesMap(const QString& result)
{
    auto result_local = result;
    result_local = output_filter->filteredOutput(result_local);
    static QRegularExpression new_line_expression("\n");
    QStringList splitted_list{result_local.split(new_line_expression)};
    auto splitted_lines = output_filter->filteredLines(splitted_list, output_filter->startsFromNumber);

    for (const auto& line : splitted_lines)
    {
        addLineToDirectoriesMap(line);
    }
}


void DownloadCommandParser::addLineToDirectoriesMap(const QString& line)
{
    static QRegularExpression directory_line_regex("(\\d+)(\\D+:\\s+)(/.*)");

    if (!directory_line_regex.isValid())
    {
        Logger::logger()->logDebug("Regex of directory line during package download is invalid!");
        return;
    }

    auto match = directory_line_regex.match(line);
    if (match.hasMatch() && directory_line_regex.captureCount() == 3)
    {
        QString full_path_with_package = match.captured(3) + "/" + package_name;
        directories_map.insert(match.captured(1).toInt(), full_path_with_package);
    }
}

void DownloadCommandParser::processForDirectories(const QString& filtered_line, int& directories_line_count)
{
    QRegExp directories_regex{"\\d+\\s+\\D+:\\s+/.*"};

    if (directories_regex.exactMatch(filtered_line))
        directories_line_count++;

    if (directories_line_count >= 2)
    {
        emit continuePathsRetrieve(result_output);
        fillDirectoriesMap(result_output);
        result_output.clear();
        directories_line_count = 0;
    }
}

void DownloadCommandParser::processForRepos()
{
    if (result_output.contains(QRegExp("\\s+\\d+\\.\\s+")))
        emit continueReposRetrieve(result_output);
}


void DownloadCommandParser::showWarningWhenNameEmpty()
{
    QMessageBox::warning(parent, i18n("Package Name"),
                         i18n("Package name cannot be empty"),
                         QMessageBox::Ok);
    Logger::logger()->logWarning("Given package name for download is empty!");
}


QStringList DownloadCommandParser::retrieveInfo()
{
    return QStringList();
}


bool DownloadCommandParser::validateFinishedOutput(int exit_code)
{
   Q_UNUSED(exit_code)

    if (isTerminated)
       return false;

   if (!isPackageAlreadyDownloaded())
   {
       QMessageBox::warning(parent, i18n("Package download failure"), i18n("Package couldn't be downloaded:\n\nError lines:\n%1", error_lines.join("\n")));
       Logger::logger()->logWarning(QStringLiteral("Package couldn't be downloaded:\n\nError lines:\n %1").arg(error_lines.join("\n")));
       return false;
   }

   QMessageBox::information(parent, i18n("Package download"), i18n("Package %1 has been downloaded %2", package_name, QString::compare(command, "pak -GB") == 0 ? i18n("and installed") : ""));
   Logger::logger()->logWarning(QStringLiteral("Package %1 has been downloaded %2").arg(package_name, QString::compare(command, "pak -GB") == 0 ? i18n("and installed") : ""));
   return true;
}


void DownloadCommandParser::showDirectory(int exit_code)
{
   Q_UNUSED(exit_code)

   if (isTerminated || !isPackageAlreadyDownloaded())
       return;

   const bool isCollectedDataValid = directory_no_choice >= 0 &&
       directories_map.contains(directory_no_choice);

   if (isCollectedDataValid &&
       QMessageBox::information(parent, i18n("Directory"),
       i18n("Do you want to open directory?"),
       QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
   {
       QDesktopServices::openUrl(QUrl::fromLocalFile(directories_map.value(directory_no_choice)));
   }
}
