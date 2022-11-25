#include "checkpackage.h"

#include <QRegularExpression>


CheckPackage::CheckPackage(QString& package_content) :
    Package(package_content)
{
    updateData(package_content);
    setText(getName() + "-" + getVersion());
    setFlags(flags() | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Unchecked);
}


CheckPackage::CheckPackage(CheckPackage& check_package) :
    Package(check_package)
{
   setName(check_package.getName());
   setVersion(check_package.getVersion());
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

    QString name_part = packageContent.left(first_whitespace_index);
    setName(name_part);

    QString version_part = packageContent.mid(first_number_index);
    setVersion(version_part);
}
