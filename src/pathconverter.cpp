#include "pathconverter.h"
#include "pakGuiSettings.h"


QString PathConverter::toAbsolutePath(const QString& new_path)
{
    QString path = new_path;
    if (path.startsWith("~/"))
        return path.remove(0, 1).prepend(QDir().homePath());

    return path;
}


QString PathConverter::fullConfigPath()
{
    return toAbsolutePath(pakGuiSettings::logs_filepath()).append("/" + pakGuiSettings::logs_filename());
}
