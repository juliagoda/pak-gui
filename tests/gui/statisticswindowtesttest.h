#include "statistics.h"

#include "packagescolumnfixtures.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockStatisticsWindow : public Statistics
{
    Q_OBJECT

public:
    explicit MockStatisticsWindow(const QMap<QString, uint>& new_statistics_map,
                                  QWidget* parent = nullptr);
    friend class TestStatisticsWindow;
};



class TestStatisticsWindow : public QObject
{
    Q_OBJECT

public:
    TestStatisticsWindow(QObject* parent = nullptr);

private slots:
    void cleanup();

private:
    QMap<QString, uint> map;
    MockStatisticsWindow statistics_window;
};
