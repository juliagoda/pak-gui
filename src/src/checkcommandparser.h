#pragma once

#include "commandparser.h"
#include "package.h"
#include "qprocess.h"

#include <QHash>


class CheckCommandParser : public CommandParser
{
    Q_OBJECT

public:
    CheckCommandParser();
    ~CheckCommandParser() override = default;

    QStringList retrieveInfo() override { return QStringList(); };
    QHash<QString, Package::Source> retrieveInfoMap();

protected:
    virtual QString generatePakCheckResults();
    virtual bool finishProcessBeforeEnd(bool starts_from_double_colon, const QString& current_source_line);

private:
    QHash<QString, Package::Source> line_to_source_map;
    QScopedPointer<QProcess> pacman_qi = QScopedPointer<QProcess>(nullptr);
};

