#include "downloadcommandparser.h"
#include "outputfilter.h"
#include "qnamespace.h"
#include "qscopedpointer.h"
#include "qtimer.h"

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
    result_output()
{
    // TODO - "tput: No value for $TERM and no -T specified"  -
    // https://stackoverflow.com/questions/29979966/tput-no-value-for-term-and-no-t-specified-error-logged-by-cron-process
    pak_download->setProcessChannelMode(QProcess::MergedChannels);
     QObject::connect(pak_download.get(), &QProcess::errorOccurred, [=]() { qDebug() << "Error in Process: " << pak_download->errorString();});
     QObject::connect(pak_download.get(), &QProcess::readyReadStandardOutput, [=]() mutable {
       while (pak_download.data()->canReadLine())
       {
           QString line = pak_download.data()->readLine();
           result_output += line;

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

    pak_download->start("/bin/bash", QStringList() << "-c" << command << package_name);
    pak_download->waitForStarted();
    pak_download->waitForReadyRead(1000);
}

void DownloadCommandParser::inputAnswer(const QString& new_answer)
{
    if (pak_download->state() != QProcess::Running && !pak_download->isWritable())
    {
        qWarning() << "Download command parser process is not running. Answer input is not possible";
        return;
    }

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

}
