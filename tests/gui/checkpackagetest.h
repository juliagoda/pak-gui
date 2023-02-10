 #include "checkpackage.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockCheckPackage : public CheckPackage
{
    Q_OBJECT

public:
    explicit MockCheckPackage(const QString& package_content,
                              Package::Source new_source);
    friend class TestCheckPackage;
};




class TestCheckPackage : public QObject
{
    Q_OBJECT

public:
    TestCheckPackage(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockCheckPackage check_package;
};
