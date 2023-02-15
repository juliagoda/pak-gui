#pragma once

#include "settings.h"
#include "logger.h"

#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <QRegularExpression>


class Package : public QListWidgetItem
{
public:
    enum class Source
    {
        Repo = 0,
        AUR,
        POLAUR,
        Unknown
    };

    Package(const QString& package_content, Source new_source) :
        QListWidgetItem(),
        name(),
        version(),
        source(new_source),
        no(0)
    {
        Q_UNUSED(package_content)
    }

    Package(Package& package) :
        QListWidgetItem()
    {
        name = package.name;
        version = package.version;
        source = package.source;
        no = package.no;
    }

    virtual ~Package() override = default;

    virtual int getNo() const { return no; };
    virtual const QString& getName() const { return name; };
    virtual const QString& getVersion() const { return version; };
    virtual Package::Source getSource() const { return source; }

    virtual void setNo(const int new_no) { no = new_no; };

protected:
    virtual void updateData(QString& packageContent, int name_line, int version_line)
    {
        QStringList lines = packageContent.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

        if (lines.count() == 0)
            return;

        setToolTipOnPackage(packageContent);

        if (!validate(lines, name_line + 1, QString("updateData()")))
            return;

        int name_separator_index = lines.at(name_line).indexOf(": ") + 1;
        setName(lines.at(name_line).mid(name_separator_index));

        if (!validate(lines, version_line + 1, QString("updateData()")))
            return;

        int version_separator_index = lines.at(version_line).indexOf(": ") + 1;
        setVersion(lines.at(version_line).mid(version_separator_index));
    }

    void setToolTipOnPackage(const QString& text)
    {
        auto selected_info_list = Settings::records()->packagesInfoSelected();
        decltype(selected_info_list)::iterator selected_info_it;
        QStringList selected_infos = QStringList();

        for(selected_info_it = selected_info_list.begin(); selected_info_it != selected_info_list.end(); selected_info_it++)
        {
            QRegularExpression regex(QStringLiteral("(%1.*)\\n").arg(*selected_info_it));
            selected_infos.append(regex.match(text).captured(1));
        }

        setToolTip(selected_infos.join(QString("\n")));
    }

    bool validate(const QStringList& lines, int expected_size, const QString& funtion_name)
    {
        if (lines.size() < expected_size)
        {
            Logger::logger()->logFatal(QString("There is not enough lines in list. Abort %1").arg(funtion_name));
            return false;
        }

        return true;
    }

    virtual void setName(const QString& new_name) { name = new_name; };
    virtual void setVersion(const QString& new_version) { version = new_version; };
    virtual void setSource(Source new_source) { source = new_source; }

    QString name;
    QString version;
    Package::Source source;
    int no;
};
