 #include "downloadcommandparser.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockDownloadCommandParser : public DownloadCommandParser
{
    Q_OBJECT

public:
    explicit MockDownloadCommandParser(const QString& new_package_name, QWidget* new_parent);
    friend class TestDownloadCommandParser;
};




class TestDownloadCommandParser : public QObject
{
    Q_OBJECT

public:
    TestDownloadCommandParser(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockDownloadCommandParser download_command_parser;
};
