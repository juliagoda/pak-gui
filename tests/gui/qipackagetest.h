 #include "qipackage.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockQiPackage : public QiPackage
{
    Q_OBJECT

public:
    explicit MockQiPackage(QString& package_content);
    friend class TestQiPackage;
};



class TestQiPackage : public QObject
{
    Q_OBJECT

public:
    TestQiPackage(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    QString package_name = "";
    MockQiPackage qi_package;
};
