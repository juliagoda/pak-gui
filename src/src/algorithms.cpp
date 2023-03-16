#include "algorithms.h"
#include "package.h"

Algorithms::Algorithms()
{

}

template<typename T>
QStringList Algorithms::createSplittedList(const QString& text,
                                           const QString& splitting_text,
                                           const QList<T>& list,
                                           const QMap<int, T>& map)
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

    auto lines_list = text.split('\n');
    int i = 0;
    int last_index = -1;
    int index_of_double_colon = 0;

    for (auto line_it = lines_list.begin(); line_it != lines_list.end(); line_it++)
    {
        if ((*line_it).contains(splitting_text))
        {
            i++;
            index_of_double_colon = (*line_it).indexOf(splitting_text) + splitting_text.count();
            auto tooltip_part = map.value(i);
            if (list.contains(tooltip_part))
            {
                selected_infos[list.indexOf(tooltip_part)] = *line_it;
                last_index = list.indexOf(tooltip_part);
            }
            else
            {
                last_index = -1;
            }

            continue;
        }

        if (last_index < 0)
            continue;

        QString leading_whitespaces{};
        selected_infos[last_index] += "\n" + leading_whitespaces.fill(' ', index_of_double_colon) + *line_it;
    }

    return selected_infos;
}


template QStringList Algorithms::createSplittedList(const QString& text, const QString& splitting_text, const QList<Package::TooltipLine>& list, const QMap<int, Package::TooltipLine>& map);
