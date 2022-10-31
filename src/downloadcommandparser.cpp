#include "downloadcommandparser.h"

#include <QProcess>
#include <QString>
#include <QRegularExpression>

DownloadCommandParser::DownloadCommandParser(const QString& new_package_name, bool new_is_built) :
    pak_download(new QProcess),
    package_name(new_package_name),
    parameter(new_is_built ? QString("pak -GB") : QString("pak -G"))
{

}

void DownloadCommandParser::updatePackageName(const QString& new_package_name)
{
    package_name = new_package_name;
}

QStringList DownloadCommandParser::getPaths()
{
    pak_download->start("/bin/bash", QStringList() << "-c" << parameter << package_name);
    pak_download->waitForStarted();
    pak_download->waitForReadyRead();
    QString output(pak_download->readAll());
    pak_download->closeReadChannel(QProcess::StandardOutput);
    return output.split(QRegularExpression("(([0-9]+\\s.*\\/)|(\\s?[0-9]+\\.\\s[\\w-]+)){1}"));
}

void DownloadCommandParser::inputAnswer(const QString& new_answer)
{
    pak_download->write(QString(new_answer + "\n").toStdString().c_str());
    pak_download->waitForBytesWritten();
    pak_download->closeWriteChannel();
}

QStringList DownloadCommandParser::retrieveInfo()
{
    pak_download->waitForReadyRead();
    QString output(pak_download->readAllStandardOutput());
    pak_download->closeReadChannel(QProcess::StandardOutput);
    return output.split(QRegularExpression("(([0-9]+\\s.*\\/)|(\\s?[0-9]+\\.\\s[\\w-]+)){1}"));
}
