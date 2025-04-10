#ifndef SENSORCHART_H
#define SENSORCHART_H

#include <QObject>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QScatterSeries>
#include <QTimer>

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
    void setSeriesColor(const QColor &color);
    void setSeriesStyle(Qt::PenStyle style, int width);
    void enableAutoScroll();
    bool userInteracting = false;
    QTimer *autoScrollTimer = nullptr;
    bool eventFilter(QObject *obj, QEvent *event);
    void setAxisRange(double minY, double maxY);
    void applyEditorSettings(const QColor &color, Qt::PenStyle style, int width, double minY, double maxY, ChartType type);

private:
    QChart *chart;
    QChartView *chartView;
    QAbstractSeries *series;
    // QLineSeries *series; // Wersja ze stałymi wykresami
    QValueAxis *axisX, *axisY;
    int dataCount;
};

#endif // SENSORCHART_H
