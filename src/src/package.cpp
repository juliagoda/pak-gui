#include "package.h"

#include "settings.h"
#include "logger.h"


Package::Package(const QString& package_content, Source new_source) :
    QListWidgetItem(),
    source{new_source}
{
    Q_UNUSED(package_content)
}


Package::Package(Package& package) :
    QListWidgetItem()
{
    name = package.name;
    version = package.version;
    source = package.source;
    no = package.no;
}


int Package::getNo() const
{
    return no;
}


const QString &Package::getName() const
{
    return name;
}


const QString &Package::getVersion() const
{
    return version;
}


Package::Source Package::getSource() const
{
    return source;
}


void Package::setNo(const int new_no)
{
    no = new_no;
}


void Package::updateData(const QString& package_content, int name_line, int version_line)
{
    QStringList lines = package_content.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

    if (lines.count() == 0)
        return;

    setToolTipOnPackage(package_content);

    if (!validate(lines, name_line + 1, QString("updateData()")))
        return;

    int name_separator_index = lines.at(name_line).indexOf(": ") + 1;
    setName(lines.at(name_line).mid(name_separator_index));

    if (!validate(lines, version_line + 1, QString("updateData()")))
        return;

    int version_separator_index = lines.at(version_line).indexOf(": ") + 1;
    setVersion(lines.at(version_line).mid(version_separator_index));
}


void Package::setToolTipOnPackage(const QString& text)
{
    auto selected_info_list = Settings::records()->packagesInfoSelected();
    QStringList selected_infos{};
    int selected_info_size = selected_info_list.count();

    while (selected_info_size > 0)
    {
        selected_infos.append("");
        --selected_info_size;
    }

    Q_ASSERT(selected_infos.count() == selected_info_list.count());

    if (text.isEmpty() || selected_infos.isEmpty())
        return;

    auto lines_list = text.split('\n');
    int i = 0;
    int last_index = -1;
    int index_of_double_colon = 0;

    for (auto line_it = lines_list.begin(); line_it != lines_list.end(); line_it++)
    {
        if ((*line_it).contains(" : "))
        {
            i++;
            index_of_double_colon = (*line_it).indexOf(" : ") + 3;
            auto tooltip_part = numberToTooltipLine.value(i, Package::TooltipLine::Unknown);
            if (selected_info_list.contains(tooltip_part))
            {
                selected_infos[selected_info_list.indexOf(tooltip_part)] = *line_it;
                last_index = selected_info_list.indexOf(tooltip_part);
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

    setToolTip(selected_infos.join(QString("\n")));
}


bool Package::validate(const QStringList& lines, int expected_size, const QString&  funtion_name)
{
    if (lines.size() < expected_size)
    {
        Logger::logger()->logFatal(QString("There are not enough lines in list. Abort %1").arg(funtion_name));
        return false;
    }

    return true;
}


void Package::setName(const QString &new_name)
{
    name = new_name;
}


void Package::setVersion(const QString &new_version)
{
    version = new_version;
}


void Package::setSource(Source new_source)
{
    source = new_source;
}


void Package::buildTooltipsLinesMap()
{
    numberToTooltipLine.insert(1, Package::TooltipLine::Name);
    numberToTooltipLine.insert(2, Package::TooltipLine::Version);
    numberToTooltipLine.insert(3, Package::TooltipLine::Description);
    numberToTooltipLine.insert(9, Package::TooltipLine::DependsOn);
}
