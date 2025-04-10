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
 * @brief Klasa odpowiedzialna za jeden wykres czujnika w systemie Mini SCADA.
 *
 * Umożliwia dodawanie danych, automatyczne przewijanie osi X, dynamiczne skalowanie osi Y
 * oraz zmianę typu wykresu (liniowy, punktowy).
 */
class SensorChart : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Konstruktor wykresu czujnika.
     * @param title Tytuł wykresu.
     * @param minY Minimalna wartość osi Y.
     * @param maxY Maksymalna wartość osi Y.
     * @param parent Wskaźnik na obiekt rodzica.
     */
    explicit SensorChart(const QString &title, double minY, double maxY, QWidget *parent = nullptr);

    /**
     * @brief Dodaje punkt danych do wykresu.
     * @param value Wartość pomiaru.
     */
    void addDataPoint(double value);

    /**
     * @brief Czyści dane z wykresu.
     */
    void clearChart();

    /**
     * @brief Zwraca wskaźnik do widoku wykresu.
     * @return QChartView* wskaźnik do widoku.
     */
    QChartView* getChartView() const; // Getter do wyświetlenia wykresu w GUI

    /**
     * @brief Zwraca wskaźnik do aktualnej serii danych.
     * @return QAbstractSeries* seria danych.
     */
    QAbstractSeries* getSeries() const;

    /**
     * @brief Zwraca wskaźnik do osi Y.
     * @return QValueAxis* oś Y.
     */
    QValueAxis* getAxisY() const;

    /**
     * @brief Typy wykresu wspierane przez klasę.
     */
    enum class ChartType {Line, Scatter};

    /**
     * @brief Zmienia typ wykresu (liniowy lub punktowy).
     * @param newType Nowy typ wykresu.
     */
    void changeType(ChartType newType);
    bool userXRangeActive = false;

    /**
     * @brief Wyłącza ręczne przewijanie wykresu.
     */
    void resetAutoScroll();

    /**
     * @brief Ustawia kolor linii wykresu.
     * @param color Kolor.
     */
    void setSeriesColor(const QColor &color);

    /**
     * @brief Ustawia styl i grubość linii.
     * @param style Styl linii (np. Qt::SolidLine).
     * @param width Grubość linii.
     */
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
