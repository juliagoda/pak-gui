#include "checkpackage.h"

#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>


CheckPackage::CheckPackage(QString& package_content) :
    Package(package_content)
{
    updateData(package_content);
    setText(getName() + "-" + getVersion());
    setFlags(flags() | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Unchecked);
}


void CheckPackage::updateData(QString& packageContent)
{
    if (packageContent.isEmpty())
        return;

    int first_whitespace_index = packageContent.indexOf(QRegularExpression(" "), 0);
    int first_number_index = packageContent.indexOf(QRegularExpression("[0-9]"), 0);
    QRegularExpression regex("[^m]*m(?<from>.*)\\[^m]*m(?<sign>.*)\\[^m]*m(?<to>.*)\\.*");

    if (!regex.isValid()) {
        QString errorString = regex.errorString(); // errorString == "missing )"
        int errorOffset = regex.patternErrorOffset(); // errorOffset == 22
    }

    QString name_part = packageContent.left(first_whitespace_index);
    setName(name_part);

    QString version_part = packageContent.mid(first_number_index);
    int first_m_index = packageContent.indexOf(QRegularExpression("m"), 0);
    int first_backslash_index = packageContent.indexOf(QRegularExpression("\\"), 0);
    int last_m_index = packageContent.lastIndexOf(QRegularExpression("m"), -2);
    int last_backslash_index = packageContent.lastIndexOf(QRegularExpression("\\"), 0);

    QString p1 = version_part.mid(first_m_index, version_part.length() - first_backslash_index);
    QString p2 = version_part.mid(last_m_index, version_part.length() - last_backslash_index);
    setVersion(version_part);
}
