#pragma once

#include <QObject>
#include <KMainWindow>
#include <QPieSlice>
#include <QPointer>
#include <QMap>
#include <QString>

class Statistics : public KMainWindow
{
    Q_OBJECT
public:
    explicit Statistics(const QMap<QString, uint>& new_statistics_map,
                        QWidget* parent = nullptr);
    virtual ~Statistics() = default;
    void init();

private Q_SLOTS:
    void updateSlice(QtCharts::QPieSlice* pie_slice);

private:
    QMap<QString, uint> statistics_map;
    QPointer<QtCharts::QPieSlice> last_pie_slice;

    void createSeries(QPointer<QtCharts::QPieSeries>& pie_series);

};

