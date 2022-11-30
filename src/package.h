#pragma once

#include "settings.h"
#include "pakGuiSettings.h"

#include <QListWidgetItem>
#include <QString>
#include <QRegularExpression>


class Package : public QListWidgetItem
{
public:
    Package(QString& package_content) :
        QListWidgetItem(),
        name(),
        version()
    {
        Q_UNUSED(package_content)
    }

    Package(Package& package) :
        QListWidgetItem()
    {
        name = package.name;
        version = package.version;
    }

    virtual const QString& getName() { return name; };
    virtual const QString& getVersion() const { return version; };

protected:
    virtual void updateData(QString& packageContent, int name_line, int version_line)
    {
        QStringList lines = packageContent.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

        if (lines.count() == 0)
            return;

        setToolTipOnPackage(packageContent);

        int name_separator_index = lines.at(name_line).indexOf(": ") + 1;
        setName(lines.at(name_line).mid(name_separator_index));

        int version_separator_index = lines.at(version_line).indexOf(": ") + 1;
        setVersion(lines.at(version_line).mid(version_separator_index));
    }

    void setToolTipOnPackage(const QString& text)
    {
        auto selected_info_list = !Settings::getPackagesInfoList().isEmpty() ?
                    Settings::getPackagesInfoList() :
                    pakGuiSettings::packages_info_selected();

        decltype(selected_info_list)::iterator selected_info_it;
        QStringList selected_infos = QStringList();
        for(selected_info_it = selected_info_list.begin(); selected_info_it != selected_info_list.end(); selected_info_it++)
        {
            QRegularExpression regex(QStringLiteral("(%1.*)\\n").arg(*selected_info_it));
            selected_infos.append(regex.match(text).captured(1));
        }

        setToolTip(selected_infos.join(QString("\n\n")));
    }

    virtual void setName(const QString& new_name) { name = new_name; };
    virtual void setVersion(const QString& new_version) { version = new_version; };

    QString name;
    QString version;
};
