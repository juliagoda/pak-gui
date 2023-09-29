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

#include "previewdesign.h"

#include "settings.h"


void PreviewDesign::update(QPointer<QTextBrowser> preview)
{
    preview->setStyleSheet(generateCss());
    preview->update();
}


QString PreviewDesign::generateCss()
{
    QStringList css_lines;
    appendBackgroundColor(css_lines);
    appendFontColor(css_lines);
    appendFontSize(css_lines);
    appendFontFamily(css_lines);
    QString generated_css = css_lines.join("; ");
    return generated_css;
}


void PreviewDesign::appendBackgroundColor(QStringList& css_lines)
{
    css_lines.append(QStringLiteral("background-color: %1").arg(Settings::records()->backgroundPreviewColor().name(QColor::HexArgb)));
}


void PreviewDesign::appendFontColor(QStringList& css_lines)
{
    css_lines.append(QStringLiteral("color: %1").arg(Settings::records()->previewFontColor().name(QColor::HexArgb)));
}


void PreviewDesign::appendFontSize(QStringList& css_lines)
{
    css_lines.append(QStringLiteral("font-size: %1").arg(Settings::records()->previewFontSize()));
}


void PreviewDesign::appendFontFamily(QStringList& css_lines)
{
    css_lines.append(QStringLiteral("font-family: %1").arg(Settings::records()->previewFontFamily()));
}
