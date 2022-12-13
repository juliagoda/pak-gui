#include "pathconverter.h"

#include "settings.h"


QString PathConverter::toAbsolutePath(const QString& new_path)
{
    QString path = new_path;
    if (path.startsWith("~/"))
        return path.remove(0, 1).prepend(QDir().homePath());

    return path;
}


QString PathConverter::fullConfigPath()
{
    QString path = Settings::records()->logsFilePath();
    return path.append("/" + Settings::records()->logsFileName());
}
