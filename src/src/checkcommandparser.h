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
    virtual ~CheckCommandParser() override = default;

    QStringList retrieveInfo() override { return QStringList(); };
    QHash<QString, Package::Source> retrieveInfoMap();

protected:
    virtual QString generatePakCheckResults();
    virtual bool finishProcessBeforeEnd(bool starts_from_double_colon, int double_colon_line_count);

private:
    bool processCurrentLine(uint& double_colon_line_count,
                            QHash<QString, Package::Source>& system_packages,
                            const QString& new_line);

    QHash<uint, Package::Source> line_to_source_map;
    QScopedPointer<QProcess> pacman_qi = QScopedPointer<QProcess>(nullptr);
};

