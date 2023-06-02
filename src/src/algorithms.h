#pragma once

#include <QString>
#include <QStringList>
#include <QMap>

class Algorithms
{
public:
    template<typename T>
    QStringList createSplittedList(const QString& text,
                                   const QString& separator,
                                   const QList<T>& list,
                                   const QHash<int, T>& map);

private:
    template<typename T>
    void createListOfLines(QStringList& selected_infos,
                           const QString& text,
                           const QString& separator,
                           const QList<T>& list,
                           const QHash<int, T>& map);


    template<typename T>
    bool foundIndexOdSeparator(const QStringList::iterator& line_it,
                               const QString& separator,
                               int& index_of_separator,
                               const QList<T>& list,
                               const QHash<int, T>& map,
                               int& i,
                               QStringList& selected_infos,
                               int& last_index);

    template<typename T>
    int getFirstIndexAfterSeparator(const QList<T>& list,
                                    T tooltip_part,
                                    QStringList& selected_infos,
                                    const QStringList::iterator& line_it);
};

