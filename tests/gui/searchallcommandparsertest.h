 #include "searchallcommandparser.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockSearchAllCommandParser : public SearchAllCommandParser
{
    Q_OBJECT

public:
    explicit MockSearchAllCommandParser(const QString& new_package_name);
    friend class TestSearchAllCommandParser;
};




class TestSearchAllCommandParser : public QObject
{
    Q_OBJECT

public:
    TestSearchAllCommandParser(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockSearchAllCommandParser search_all_command_parser;
};



