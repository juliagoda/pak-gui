#include "downloadcommandparser.h"

#include "outputfilter.h"
#include "qmessagebox.h"

#include <KLocalizedString>
#include <QScopedPointer>
#include <QMessageBox>
#include <QProcess>
#include <QString>
#include <QRegularExpression>
#include <QMessageBox>
#include <QtDebug>
#include <QtConcurrent/QtConcurrent>

DownloadCommandParser::DownloadCommandParser(const QString& new_package_name) :
    pak_download(new QProcess),
    package_name(new_package_name),
    command(QString("pak -G")),
    result_output(),
    error_lines()
{
    pak_download->setProcessChannelMode(QProcess::MergedChannels);
    QObject::connect(pak_download.get(), QOverload<int>::of(&QProcess::finished), this, &DownloadCommandParser::validateFinishedOutput);
    QObject::connect(pak_download.get(), &QProcess::errorOccurred, [=]() { qDebug() << "Error in Process: " << pak_download->errorString();});
    QObject::connect(pak_download.get(), &QProcess::readyReadStandardOutput, [=]() mutable {
        while (pak_download.data()->canReadLine())
        {
            QString line = pak_download.data()->readLine();
            auto filtered_line = OutputFilter::filteredOutput(line);
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
        }});
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
        qWarning() << "retrieving paths from download command parser is not possible";

    qInfo() << "Trying download package: " << package_name << " with command " << command.trimmed();

    pak_download->start("/bin/bash", QStringList() << "-c" << command + " " + package_name.trimmed());
    pak_download->waitForStarted();
    pak_download->waitForReadyRead();
}


void DownloadCommandParser::inputAnswer(const QString& new_answer)
{
    if (pak_download->state() != QProcess::Running && !pak_download->isWritable())
    {
        qWarning() << "Download command parser process is not running. Answer input is not possible";
        return;
    }

    qInfo() << "Chosen option: " << new_answer;

    pak_download->write(new_answer.toLocal8Bit());
    pak_download->waitForReadyRead();
}


bool DownloadCommandParser::validate()
{
    if (package_name.isEmpty())
    {
        QMessageBox::warning(new QWidget, QObject::tr("Package Name"),
                             QObject::tr("Package name cannot be empty"),
                             QMessageBox::Ok);
        return false;
    }

    if (QString::compare(command, QString("pak -GB")) != 0 &&
            QString::compare(command, QString("pak -G")) != 0)
    {
        qWarning() << "Package download command is not correct";
        return false;
    }

    return true;
}


QStringList DownloadCommandParser::retrieveInfo()
{
    return QStringList();
}


void DownloadCommandParser::validateFinishedOutput(int exit_code)
{
   Q_UNUSED(exit_code)
   if (!result_output.contains("PKGBUILD has been downloaded to"))
   {
       QMessageBox::critical(new QWidget, i18n("Package download failure"), i18n("Package couldn't be downloaded:\n\nError lines:\n%1", error_lines.join("\n")));
       return;
   }

   QMessageBox::information(new QWidget, i18n("Package download"), i18n("Package %1 has been downloaded %2", package_name, QString::compare(command, "pak -GB") == 0 ? i18n("and installed") : ""));
}
