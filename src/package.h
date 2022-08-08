#pragma once

#include <QCheckBox>

class Package : public QCheckBox
{
    Q_OBJECT

public:
    Package(QString& package_content);

    const QString& getName() const;
    const QString& getVersion() const;
    const QString& getDescription() const;
    const QString& getDependencies() const;

private:
    void updateData(QString &packageContent);
    void setName(const QString& new_name);
    void setVersion(const QString& new_version);
    void setDescription(const QString& new_description);
    void setDependencies(const QString& new_dependencies);

    QString name;
    QString version;
    QString description;
    QString dependencies;
};

