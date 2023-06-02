#pragma once

#include "commandparser.h"
#include "package.h"

#include <QHash>
#include <QProcess>


class CheckCommandParser : public CommandParser
{
    Q_OBJECT

public:
    CheckCommandParser();
    virtual ~CheckCommandParser() override = default;

    QStringList retrieveInfo() override { return QStringList(); };
    QHash<QString, Package::Source> retrieveInfoMap();

protected:
    virtual QString generatePakCheckResults();

private:
    void processLines(QHash<QString, Package::Source>& system_packages,
                      QStringListIterator& iterator);
    void increaseDoubleColonCounter(const QString& filtered_line, uint& counter);
    void appendPackageLine(QHash<QString, Package::Source>& system_packages,
                           const QString& filtered_line, uint &counter);

    QHash<uint, Package::Source> line_to_source_map;
    QScopedPointer<QProcess> pacman_qi = QScopedPointer<QProcess>(nullptr);
};

