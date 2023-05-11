#include "checkpackage.h"

#include <QRegularExpression>


CheckPackage::CheckPackage(QString new_package_content, Package::Source new_source) :
    Package{new_package_content, new_source}
{
    if (new_package_content.isEmpty())
        return;

    updateData(new_package_content, 0, 0);
    setText(getName() + "-" + getVersion());
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Unchecked);
}


CheckPackage::CheckPackage(CheckPackage& check_package) :
    Package{check_package}
{
   setName(check_package.getName());
   setNo(check_package.getNo());
   setVersion(check_package.getVersion());
   setText(getName().trimmed() + "-" + getVersion().trimmed());
   setFlags(check_package.flags());
   setCheckState(check_package.checkState());
}


void CheckPackage::updateData(const QString& package_content, int name_line, int version_line)
{
    Q_UNUSED(name_line)
    Q_UNUSED(version_line)

    static QRegularExpression whitespace_expression(" ");
    static QRegularExpression numbers_expression("[0-9]");
    int first_whitespace_index = package_content.indexOf(whitespace_expression);
    int first_number_index = package_content.indexOf(numbers_expression);

    QString name_part = package_content.left(first_whitespace_index);
    setName(name_part);

    QString version_part = package_content.mid(first_number_index);
    setVersion(version_part);
}
