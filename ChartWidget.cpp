#include "ChartWidget.h"
#include <QFileDialog>
#include <QTextStream>

ChartWidget::ChartWidget(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    setLayout(layout);
}

void ChartWidget::addChart(const QString &title, double minY, double maxY) {
    if (!charts.contains(title)) {
        SensorChart *chart = new SensorChart(title, minY, maxY, this);
        charts[title] = chart;
        layout->addWidget(chart->getChartView());
    }
}

void ChartWidget::addData(const QString &chartTitle, double value) {
    if (charts.contains(chartTitle)) {
        charts[chartTitle]->addDataPoint(value);
    }
}

void ChartWidget::clearAllCharts() {
    for (auto &chart : charts) {
        chart->clearChart();
    }
}

void ChartWidget::saveToCSV(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    out << "Pomiar";

    for (const auto &chartTitle : charts.keys()) {
        out << "," << chartTitle;
    }
    out << "\n";

    int maxDataPoints = 0;
    for (const auto &chart : charts) {
        maxDataPoints = qMax(maxDataPoints, chart->getSeries()->count());
    }

    for (int i = 0; i < maxDataPoints; i++) {
        out << i;
        for (const auto &chart : charts) {
            if (i < chart->getSeries()->count()) {
                out << "," << chart->getSeries()->at(i).y();
            } else {
                out << ",";
            }
        }
        out << "\n";
    }

    file.close();
}

void ChartWidget::setAxisRange(double minY, double maxY) {
    for (auto &chart : charts) {
        chart->getAxisY()->setRange(minY, maxY);
    }
}

bool ChartWidget::hasChart(const QString &title) {
    return charts.contains(title);
}


