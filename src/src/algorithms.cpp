#include "algorithms.h"
#include "package.h"


template<typename T>
QStringList Algorithms::createSplittedList(const QString& text,
                                           const QString& separator,
                                           const QList<T>& list,
                                           const QHash<int, T>& map)
{
    QStringList selected_infos{};
    int selected_info_size = list.count();

    while (selected_info_size > 0)
    {
        selected_infos.append("");
        --selected_info_size;
    }

    Q_ASSERT(selected_infos.count() == list.count());

    if (text.isEmpty() || selected_infos.isEmpty())
        return QStringList();

    createListOfLines<T>(selected_infos, text, separator, list, map);
    return selected_infos;
}


template<typename T>
void Algorithms::createListOfLines(QStringList& selected_infos,
                                   const QString& text,
                                   const QString& separator,
                                   const QList<T>& list,
                                   const QHash<int, T>& map)
{
    auto lines_list = text.split('\n');
    int i = 0;
    int last_index = -1;
    int index_of_separator = 0;

    for (auto line_it = lines_list.begin(); line_it != lines_list.end(); line_it++)
    {
        if (foundIndexOdSeparator<T>(line_it, separator, index_of_separator, list, map, i, selected_infos, last_index))
            continue;

        if (last_index < 0)
            continue;

        QString leading_whitespaces{};
        selected_infos[last_index] += "\n" + leading_whitespaces.fill(' ', index_of_separator) + *line_it;
    }
}


template<typename T>
bool Algorithms::foundIndexOdSeparator(const QStringList::iterator& line_it,
                                       const QString& separator,
                                       int& index_of_separator,
                                       const QList<T>& list,
                                       const QHash<int, T>& map,
                                       int& i,
                                       QStringList& selected_infos,
                                       int& last_index)
{
    if ((*line_it).contains(separator))
    {
        i++;
        index_of_separator = (*line_it).indexOf(separator) + separator.count();
        auto tooltip_part = map.value(i);
        last_index = getFirstIndexAfterSeparator<T>(list, tooltip_part, selected_infos, line_it);
        return true;
    }

    return false;
}



template<typename T>
int Algorithms::getFirstIndexAfterSeparator(const QList<T>& list,
                                            T tooltip_part,
                                            QStringList& selected_infos,
                                            const QStringList::iterator& line_it)
{
    if (list.contains(tooltip_part))
    {
        selected_infos[list.indexOf(tooltip_part)] = *line_it;
        return list.indexOf(tooltip_part);
    }

    return -1;
}


// forward declarations

template QStringList Algorithms::createSplittedList(const QString& text,
                                                    const QString& separator,
                                                    const QList<Package::TooltipLine>& list,
                                                    const QHash<int, Package::TooltipLine>& map);

template void Algorithms::createListOfLines(QStringList& selected_infos,
                                            const QString& text,
                                            const QString& separator,
                                            const QList<Package::TooltipLine>& list,
                                            const QHash<int, Package::TooltipLine>& map);

template bool Algorithms::foundIndexOdSeparator(const QStringList::iterator& line_it,
                                                const QString& separator,
                                                int& index_of_separator,
                                                const QList<Package::TooltipLine>& list,
                                                const QHash<int, Package::TooltipLine>& map,
                                                int& i,
                                                QStringList& selected_infos,
                                                int& last_index);

template int Algorithms::getFirstIndexAfterSeparator(const QList<Package::TooltipLine>& list,
                                                     Package::TooltipLine tooltip_part,
                                                     QStringList& selected_infos,
                                                     const QStringList::iterator& line_it);



