#include "checkpackage.h"

#include <QRegularExpression>


CheckPackage::CheckPackage(const QString& new_package_content, Package::Source new_source) :
    Package(new_package_content, new_source)
{
    QString package_content = new_package_content;
    updateData(package_content, 0, 0);
    setText(getName() + "-" + getVersion());
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Unchecked);
}


CheckPackage::CheckPackage(CheckPackage& check_package) :
    Package(check_package)
{
   setName(check_package.getName());
   setNo(check_package.getNo());
   setVersion(check_package.getVersion());
   setText(getName().trimmed() + "-" + getVersion().trimmed());
   setFlags(check_package.flags());
   setCheckState(check_package.checkState());
}


void CheckPackage::updateData(QString& packageContent, int name_line, int version_line)
{
    Q_UNUSED(name_line)
    Q_UNUSED(version_line)

    if (packageContent.isEmpty())
        return;

    int first_whitespace_index = packageContent.indexOf(QRegularExpression(" "), 0);
    int first_number_index = packageContent.indexOf(QRegularExpression("[0-9]"), 0);

    QString name_part = packageContent.left(first_whitespace_index);
    setName(name_part);

    QString version_part = packageContent.mid(first_number_index);
    setVersion(version_part);
}
