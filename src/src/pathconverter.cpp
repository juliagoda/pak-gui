// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of  package manager based on "pak" application.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

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
