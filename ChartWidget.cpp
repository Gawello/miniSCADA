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

        QChartView *view = chart->getChartView();
        if (view) {
            layout->addWidget(view);
            qDebug() << "[ChartWidget] Dodano nowy wykres:" << title;
        } else {
            qDebug() << "[ChartWidget] Uwaga: getChartView() zwrócił nullptr dla:" << title;
        }
    } else {
        qDebug() << "[ChartWidget] Wykres już istnieje:" << title;
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

    // Ustal maksymalną długość serii
    for (const auto &chart : charts) {
        auto xySeries = qobject_cast<QXYSeries*>(chart->getSeries());
        if (xySeries) {
            maxDataPoints = qMax(maxDataPoints, xySeries->count());
        }
    }

    // Zapisujemy dane do pliku
    for (int i = 0; i < maxDataPoints; i++) {
        out << i;
        for (const auto &chart : charts) {
            auto xySeries = qobject_cast<QXYSeries*>(chart->getSeries());
            if (xySeries && i < xySeries->count()) {
                out << "," << xySeries->at(i).y();
            } else {
                out << ",";
            }
        }
        out << "\n";
    }

    file.close();
}

void ChartWidget::setAxisRange(const QString &chartTitle, double minY, double maxY) {
    if (!charts.contains(chartTitle)) {
        qDebug() << "[ChartWidget] Brak wykresu o nazwie:" << chartTitle;
        return;
    }

    QValueAxis *axis = charts[chartTitle]->getAxisY();
    if (axis) {
        axis->setRange(minY, maxY);
        qDebug() << "[ChartWidget] Zakres Y ustawiony dla:" << chartTitle << "min:" << minY << "max:" << maxY;
    } else {
        qDebug() << "[ChartWidget] Brak osi Y w wykresie:" << chartTitle;
    }
}

bool ChartWidget::hasChart(const QString &title) {
    return charts.contains(title);
}


void ChartWidget::changeChartType(const QString &chartTitle, const QString &typeName) {
    if (!charts.contains(chartTitle)) {
        qDebug() << "[ChartWidget] Nie znaleziono wykresu:" << chartTitle;
        return;
    }

    SensorChart::ChartType type;

    if (typeName == "Line") {
        type = SensorChart::ChartType::Line;
    } else if (typeName == "Scatter") {
        type = SensorChart::ChartType::Scatter;
    } else {
        qDebug() << "[ChartWidget] Nieznany typ wykresu:" << typeName;
        return;
    }

    charts[chartTitle]->changeType(type);
    qDebug() << "[ChartWidget] Typ wykresu zmieniony na:" << typeName << "dla" << chartTitle;
}


QStringList ChartWidget::getChartTitles() const {
    return charts.keys();
}

void ChartWidget::setChartColor(const QString &chartTitle, const QColor &color) {
    if (!charts.contains(chartTitle)) return;

    charts[chartTitle]->setSeriesColor(color);
}

void ChartWidget::setChartStyle(const QString &chartTitle, Qt::PenStyle style, int width) {
    if (!charts.contains(chartTitle)) return;

    charts[chartTitle]->setSeriesStyle(style, width);
}


