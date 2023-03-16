#pragma once

#include <QString>
#include <QStringList>
#include <QMap>

class Algorithms
{
public:
    template<typename T>
    QStringList createSplittedList(const QString& text,
                                   const QString& splitting_text,
                                   const QList<T>& list,
                                   const QMap<int, T>& map);
};

