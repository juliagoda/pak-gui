 #include "installcommandparser.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockInstallCommandParser : public InstallCommandParser
{
    Q_OBJECT

public:
    explicit MockInstallCommandParser();
    friend class TestInstallCommandParser;
};




class TestInstallCommandParser : public QObject
{
    Q_OBJECT

public:
    TestInstallCommandParser(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockInstallCommandParser install_command_parser;
};
