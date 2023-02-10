#include "progressview.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockProgressView : public ProgressView
{
    Q_OBJECT

public:
    explicit MockProgressView(QDialog* parent = nullptr);
    friend class TestAvailablePackagesColumn;
};




class TestProgressView : public QObject
{
    Q_OBJECT

public:
    TestProgressView(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    MockProgressView progress_view;
};
