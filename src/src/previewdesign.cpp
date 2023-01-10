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
