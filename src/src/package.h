#pragma once

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

    Package(const QString& package_content, Source new_source);

    Package(Package& package);

    ~Package() override = default;

    virtual int getNo() const;
    virtual const QString& getName() const;
    virtual const QString& getVersion() const;
    virtual Package::Source getSource() const;

    virtual void setNo(const int new_no);;

protected:
    virtual void updateData(QString& packageContent, int name_line, int version_line);

    void setToolTipOnPackage(const QString& text);

    bool validate(const QStringList& lines, int expected_size, const QString& funtion_name);

    virtual void setName(const QString& new_name);
    virtual void setVersion(const QString& new_version);
    virtual void setSource(Source new_source);

    QString name;
    QString version;
    Package::Source source;
    int no;
};
