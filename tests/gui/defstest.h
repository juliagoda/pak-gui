#pragma once

#include <QtTest/QtTest>
#include <QWidget>


class TestDefs : public QObject
{
    Q_OBJECT

public:
    TestDefs(QObject* parent = nullptr);

private slots:
    void packageQiNameLineIsEqualToZero();
    void packageQiVersionLineIsEqualToOne();
    void packageSiRepoNameIsEqualToZero();
    void packageSiNameLineIsEqualToOne();
    void packageSiVersionLineIsEqualToTwo();
    void execFilesHaveCorrectNames();
    void ksshAskPassCommandIsCorrect();
    void taskToWriteOperationMapHasCorrectValues();
};
