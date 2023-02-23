#include "downloadcommandparser.h"

#include "outputfilter.h"
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


DownloadCommandParser::DownloadCommandParser(const QString& new_package_name,
                                             QWidget* new_parent) :
    package_name(new_package_name),
    parent(new_parent)
{
    connectSignals();
}


void DownloadCommandParser::connectSignals()
{
    pak_download.reset(new QProcess);
    pak_download->setProcessChannelMode(QProcess::MergedChannels);

    if (pak_download.isNull())
        return;

    QObject::connect(pak_download.get(), QOverload<int>::of(&QProcess::finished), this, &DownloadCommandParser::validateFinishedOutput);
    QObject::connect(pak_download.get(), &QProcess::errorOccurred, this, [this]() { Logger::logger()->logWarning(QStringLiteral("Error during download: %1").arg(pak_download->errorString())); });

    QObject::connect(pak_download.get(), &QProcess::readyReadStandardOutput, this, [this]() mutable
    {
        while (pak_download.data()->canReadLine())
        {
            QString line = pak_download.data()->readLine();
            processReadLine(line);
        }
    });
}


void DownloadCommandParser::processReadLine(QString& line)
{
    auto filtered_line = OutputFilter::filteredOutput(line);
    Logger::logger()->writeLineToFile(filtered_line);
    result_output += filtered_line;

    if (line.contains("error:"))
        error_lines.append(filtered_line);

    if (result_output.contains("Current directory:"))
    {
        emit continuePathsRetrieve(result_output);
        result_output.clear();
    }

    if (result_output.contains(QRegExp("\\s+\\d+\\.\\s+")))
    {
        emit continueReposRetrieve(result_output);
    }
}

bool DownloadCommandParser::isPackageAlreadyDownloaded()
{
    return result_output.contains("PKGBUILD has been downloaded to");
}


void DownloadCommandParser::updatePackageName(const QString& new_package_name)
{
    package_name = new_package_name;
}


void DownloadCommandParser::updateParameter(const QString& new_command)
{
    command = new_command;
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


bool DownloadCommandParser::validate()
{
    if (package_name.isEmpty())
    {
        showWarningWhenNameEmpty();
        return false;
    }

    return true;
}


void DownloadCommandParser::showWarningWhenNameEmpty()
{
    QMessageBox::warning(parent, QObject::tr("Package Name"),
                         QObject::tr("Package name cannot be empty"),
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
