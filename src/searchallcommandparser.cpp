#include "searchallcommandparser.h"

SearchAllCommandParser::SearchAllCommandParser(const QString& new_package_name) :
    package_name(new_package_name)
{

}

QStringList SearchAllCommandParser::retrieveInfo()
{
    QScopedPointer<QProcess> pacman_qi(new QProcess);
    pacman_qi->start("/bin/bash", QStringList() << "-c" << "pak -SS " << package_name);
    pacman_qi->waitForStarted();
    pacman_qi->waitForFinished();
    QString output(pacman_qi->readAllStandardOutput());
    return output.split(QRegularExpression("(([0-9]+(\.|-){1}[0-9]+)|(\[installed\]))"));
}
