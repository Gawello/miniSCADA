#include "SensorChart.h"
#include <QVBoxLayout>

SensorChart::SensorChart(const QString &title, double minY, double maxY, QWidget *parent)
    : QWidget(parent), dataCount(0) {

    series = new QLineSeries();

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);
    chart->legend()->hide();

    axisX = new QValueAxis();
    axisX->setRange(0, 100);
    axisX->setLabelFormat("%d");
    axisX->setTitleText("Pomiar");

    axisY = new QValueAxis();
    axisY->setRange(minY, maxY);
    axisY->setTitleText(title);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void SensorChart::addDataPoint(double value) {
    if (dataCount > 1000) {
        series->remove(0);
    } else {
        dataCount++;
    }
    series->append(dataCount, value);

    axisX->setMax(dataCount);
    axisX->setMin(qMax(0, dataCount - 100));

    if (value > axisY->max()) axisY->setMax(value + 5);
    if (value < axisY->min()) axisY->setMin(value - 5);
}

void SensorChart::clearChart() {
    series->clear();
    dataCount = 0;
}

QChartView* SensorChart::getChartView() const {
    return chartView;
}


QLineSeries* SensorChart::getSeries() const {
    return series;
}


QValueAxis* SensorChart::getAxisY() const {
    return axisY;
}
