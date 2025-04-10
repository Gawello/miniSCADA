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

/**
 * @class SensorChart
 * @brief Klasa odpowiedzialna za sensorchart.
 */
class SensorChart : public QWidget {
    Q_OBJECT

public:
    /**
 * @brief Metoda SensorChart.
 */
    explicit SensorChart(const QString &title, double minY, double maxY, QWidget *parent = nullptr);
    /**
 * @brief Metoda addDataPoint.
 */
    void addDataPoint(double value);
    /**
 * @brief Metoda clearChart.
 */
    void clearChart();
    /**
 * @brief Metoda getChartView.
 */
    QChartView* getChartView() const; // Getter do wyświetlenia wykresu w GUI
    /**
 * @brief Metoda getSeries.
 */
    QAbstractSeries* getSeries() const;
    /**
 * @brief Metoda getAxisY.
 */
    QValueAxis* getAxisY() const;
    enum class ChartType {Line, Scatter};
    /**
 * @brief Metoda changeType.
 */
    void changeType(ChartType newType);
    bool userXRangeActive = false;
    /**
 * @brief Metoda resetAutoScroll.
 */
    void resetAutoScroll();
    /**
 * @brief Metoda setSeriesColor.
 */
    void setSeriesColor(const QColor &color);
    /**
 * @brief Metoda setSeriesStyle.
 */
    void setSeriesStyle(Qt::PenStyle style, int width);
    /**
 * @brief Metoda enableAutoScroll.
 */
    void enableAutoScroll();
    bool userInteracting = false;
    QTimer *autoScrollTimer = nullptr;
    /**
 * @brief Metoda eventFilter.
 */
    bool eventFilter(QObject *obj, QEvent *event);
    /**
 * @brief Metoda setAxisRange.
 */
    void setAxisRange(double minY, double maxY);
    /**
 * @brief Metoda applyEditorSettings.
 */
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
