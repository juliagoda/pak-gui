#include "sipackage.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockSiPackage : public SiPackage
{
    Q_OBJECT

public:
    explicit MockSiPackage(QString& package_content);
    friend class TestSiPackage;
};



class TestSiPackage : public QObject
{
    Q_OBJECT

public:
    TestSiPackage(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    QString package_name = "";
    MockSiPackage si_package;
};
