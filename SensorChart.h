#ifndef SENSORCHART_H
#define SENSORCHART_H

#include <QObject>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>

class SensorChart : public QWidget {
    Q_OBJECT

public:
    explicit SensorChart(const QString &title, double minY, double maxY, QWidget *parent = nullptr);
    void addDataPoint(double value);
    void clearChart();
    QChartView* getChartView() const; // Getter do wyświetlenia wykresu w GUI
    QLineSeries* getSeries() const;
    QValueAxis* getAxisY() const;

private:
    QChart *chart;
    QChartView *chartView;
    QLineSeries *series;
    QValueAxis *axisX, *axisY;
    int dataCount;
};

#endif // SENSORCHART_H
