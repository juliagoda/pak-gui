// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of  package manager based on "pak" application.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "statistics.h"

#include "logger.h"

#include <KLocalizedString>
#include <QtCharts>
#include <QVBoxLayout>


Statistics::Statistics(const QMap<QString, uint>& new_statistics_map,
                       QWidget* parent)
    : KMainWindow{parent},
      statistics_map{new_statistics_map},
      last_pie_slice{nullptr}
{
   init();
   setWindowTitle(i18n("Statistics"));
}


void Statistics::init()
{
    QPointer<QtCharts::QPieSeries> pie_series = new QtCharts::QPieSeries();
    createSeries(pie_series);
    connect(pie_series, &QtCharts::QPieSeries::clicked, this, &Statistics::updateSlice);

    QPointer<QtCharts::QChart> chart = new QtCharts::QChart();
    chart->addSeries(pie_series);
    chart->setTitle(i18n("Statistics - current month"));
    QFont font;
    font.setBold(true);
    font.setPixelSize(20);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::Dense7Pattern));
    chart->legend()->hide();

    QPointer<QtCharts::QChartView> chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    if (pie_series->count() > 0)
    {
        setCentralWidget(chartView);
        return;
    }

    createAlternateLabel();
    delete chartView;
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


void Statistics::createSeries(const QPointer<QtCharts::QPieSeries>& pie_series)
{
   QMap<QString, uint>::iterator it;
   for (it = statistics_map.begin(); it != statistics_map.end(); ++it)
   {
       QString pie_label = it.key() + " (" + QString::number(it.value()) + ")";
       Logger::logger()->logDebug(QStringLiteral("Statistics pie serie - added label \"%1\" and value \"%2\"").arg(pie_label).arg(it.value()));
       pie_series->append(pie_label, it.value());
   }
}


void Statistics::createAlternateLabel()
{
   QVBoxLayout* layout = new QVBoxLayout;
   QLabel* without_data_label = new QLabel;
   without_data_label->setText(i18n("No data for current month"));
   without_data_label->setStyleSheet("color: black; font-size: 30px; font-weight: bold;");
   layout->addWidget(without_data_label, 0, Qt::AlignCenter);
   QWidget* widget = new QWidget;
   widget->setLayout(layout);
   setCentralWidget(widget);
}

