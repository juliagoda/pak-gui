#pragma once

#include <QStringList>
#include <QPointer>
#include <QTextBrowser>
#include <QStringList>


class PreviewDesign
{
public:
    PreviewDesign();
    static void update(QPointer<QTextBrowser> preview);

private:
    static QString generateCss();
    static void appendBackgroundColor(QStringList& css_lines);
    static void appendFontColor(QStringList& css_lines);
    static void appendFontSize(QStringList& css_lines);
    static void appendFontFamily(QStringList& css_lines);
};
