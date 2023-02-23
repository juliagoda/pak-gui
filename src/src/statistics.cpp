#include "statistics.h"

#include "logger.h"

#include <QtCharts>


Statistics::Statistics(const QMap<QString, uint>& new_statistics_map,
                       QWidget* parent)
    : KMainWindow{parent},
      statistics_map{new_statistics_map},
      last_pie_slice{nullptr}
{
   init();
}


void Statistics::init()
{
    QPointer<QtCharts::QPieSeries> pie_series = new QtCharts::QPieSeries();
    createSeries(pie_series);
    connect(pie_series, &QtCharts::QPieSeries::clicked, this, &Statistics::updateSlice);

    QPointer<QtCharts::QChart> chart = new QtCharts::QChart();
    chart->addSeries(pie_series);
    chart->setTitle(tr("Statistics - current month"));
    chart->legend()->hide();

    QPointer<QtCharts::QChartView> chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(chartView);
}


void Statistics::updateSlice(QtCharts::QPieSlice* pie_slice)
{
    if (last_pie_slice)
    {
        Logger::logger()->logDebug(QStringLiteral("Changed current pie slice - Hide \"%1\"").arg(last_pie_slice->label()));
        last_pie_slice->setLabelVisible(false);
        last_pie_slice->setExploded(false);
    }

    Logger::logger()->logDebug(QStringLiteral("Changed current pie slice - Show \"%1\"").arg(pie_slice->label()));
    pie_slice->setLabelVisible(true);
    pie_slice->setExploded(true);
    last_pie_slice = pie_slice;
}


void Statistics::createSeries(QPointer<QtCharts::QPieSeries>& pie_series)
{
   QMap<QString, uint>::iterator it;
   for (it = statistics_map.begin(); it != statistics_map.end(); it++)
   {
       QString pie_label = it.key() + " (" + QString::number(it.value()) + ")";
       Logger::logger()->logDebug(QStringLiteral("Statistics pie serie - added label \"%1\" and value \"%2\"").arg(pie_label).arg(it.value()));
       pie_series->append(pie_label, it.value());
   }
}

