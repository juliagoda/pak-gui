#include "downloadcommandparser.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>
#include <QMessageBox>
#include <QDebug>

DownloadCommandParser::DownloadCommandParser(const QString& new_package_name) :
    pak_download(new QProcess),
    package_name(new_package_name),
    command(QString("pak -G"))
{

}

void DownloadCommandParser::updatePackageName(const QString& new_package_name)
{
   package_name = new_package_name;
}

void DownloadCommandParser::updateParameter(const QString& new_command)
{
   command = new_command;
}

QStringList DownloadCommandParser::getPaths()
{
    if (!validate())
    {
        qWarning() << "retrieving paths from download command parser is not possible";
        return QStringList();
    }

    pak_download->start("/bin/bash", QStringList() << "-c" << command << package_name);
    pak_download->waitForStarted();
    pak_download->waitForReadyRead();
    QString output(pak_download->readAll());
    pak_download->closeReadChannel(QProcess::StandardOutput);
    return output.split(QRegularExpression("(([0-9]+\\s.*\\/)|(\\s?[0-9]+\\.\\s[\\w-]+)){1}"));
}

void DownloadCommandParser::inputAnswer(const QString& new_answer)
{
    if (pak_download->state() != QProcess::Running)
    {
        qWarning() << "Download command parser process is not running. Answer input is not possible";
        return;
    }

    pak_download->write(QString(new_answer + "\n").toStdString().c_str());
    pak_download->waitForBytesWritten();
    pak_download->closeWriteChannel();
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
    if (pak_download->state() != QProcess::Running)
    {
        qWarning() << "Download command parser process is not running. Retrieving repos list is not possible";
        return QStringList();
    }

    pak_download->waitForReadyRead();
    QString output(pak_download->readAllStandardOutput());
    pak_download->closeReadChannel(QProcess::StandardOutput);
    return output.split(QRegularExpression("(([0-9]+\\s.*\\/)|(\\s?[0-9]+\\.\\s[\\w-]+)){1}"));
}
