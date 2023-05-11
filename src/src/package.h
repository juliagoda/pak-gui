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

    enum class TooltipLine
    {
        Name = 0,
        Version,
        Description,
        Architecture,
        URL,
        Licenses,
        Groups,
        Provides,
        DependsOn,
        OptionalDeps,
        ConflictsWith,
        Replaces,
        DownloadSize,
        RequiredBy,
        OptionalFor,
        InstalledSize,
        Packager,
        BuildDate,
        InstallDate,
        InstallReason,
        InstallScript,
        ValidatedBy,
        Unknown
    };

    Package(const QString& package_content, Source new_source);

    Package(Package& package);

    ~Package() override = default;

    virtual int getNo() const;
    virtual const QString& getName() const;
    virtual const QString& getVersion() const;
    virtual Package::Source getSource() const;

    virtual void setNo(const int new_no);

protected:
    virtual void updateData(const QString& package_content, int name_line, int version_line);

    void setToolTipOnPackage(const QString& text);

    bool validate(const QStringList& lines, int expected_size, const QString& funtion_name);

    virtual void setName(const QString& new_name);
    virtual void setVersion(const QString& new_version);
    virtual void setSource(Source new_source);
    virtual void buildTooltipsLinesMap();

    QString name{};
    QString version{};
    Package::Source source{Package::Source::Repo};
    QMap<int, TooltipLine> numberToTooltipLine{};
    int no{0};

private:
    void setNameParameter(int parameter_line,
                          const QStringList& lines);

    void setVersionParameter(int parameter_line,
                             const QStringList& lines);
};
