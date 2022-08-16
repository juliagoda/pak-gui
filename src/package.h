#pragma once

#include "qobjectdefs.h"

#include <QListWidgetItem>
#include <QString>


class Package : public QListWidgetItem
{
public:
    Package(QString& package_content) :
        QListWidgetItem(),
        name(),
        version(),
        description(),
        dependencies()
    {
        Q_UNUSED(package_content)
    }

    virtual const QString& getName() { return name; };
    virtual const QString& getVersion() const { return version; };
    virtual const QString& getDescription() const { return description; };
    virtual const QString& getDependencies() const { return dependencies; };

protected:
    virtual void updateData(QString& packageContent) { Q_UNUSED(packageContent) };
    virtual void setName(const QString& new_name) { name = new_name; };
    virtual void setVersion(const QString& new_version) { version = new_version; };
    virtual void setDescription(const QString& new_description) { description = new_description; };
    virtual void setDependencies(const QString& new_dependencies) { dependencies = new_dependencies; };

    QString name;
    QString version;
    QString description;
    QString dependencies;
};
