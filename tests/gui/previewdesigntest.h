#pragma once

#include "previewdesign.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>



class TestPreviewDesign: public QObject
{
    Q_OBJECT

public:
    TestPreviewDesign(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    PreviewDesign preview_design;
};
