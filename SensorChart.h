#ifndef SENSORCHART_H
#define SENSORCHART_H

#include <QObject>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QScatterSeries>

class SensorChart : public QWidget {
    Q_OBJECT

public:
    explicit SensorChart(const QString &title, double minY, double maxY, QWidget *parent = nullptr);
    void addDataPoint(double value);
    void clearChart();
    QChartView* getChartView() const; // Getter do wyświetlenia wykresu w GUI
    QAbstractSeries* getSeries() const;
    QValueAxis* getAxisY() const;
    enum class ChartType {Line, Scatter};
    void changeType(ChartType newType);
    bool userXRangeActive = false;
    void resetAutoScroll();

private:
    QChart *chart;
    QChartView *chartView;
    QAbstractSeries *series;
    // QLineSeries *series; // Wersja ze stałymi wykresami
    QValueAxis *axisX, *axisY;
    int dataCount;
};

#endif // SENSORCHART_H
