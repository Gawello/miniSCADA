#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include "SensorChart.h"

/**
 * @class ChartWidget
 * @brief Klasa odpowiedzialna za chartwidget.
 */
class ChartWidget : public QWidget {
    Q_OBJECT

public:
    /**
 * @brief Metoda ChartWidget.
 */
    explicit ChartWidget(QWidget *parent = nullptr);
    /**
 * @brief Metoda addChart.
 */
    void addChart(const QString &title, double minY=0, double maxY=100);
    /**
 * @brief Metoda addData.
 */
    void addData(const QString &chartTitle, double value);
    /**
 * @brief Metoda clearAllCharts.
 */
    void clearAllCharts();
    /**
 * @brief Metoda saveToCSV.
 */
    void saveToCSV(const QString &filePath);
    /**
 * @brief Metoda setAxisRange.
 */
    void setAxisRange(const QString &chartTitle, double minY=0, double maxY=100);
    /**
 * @brief Metoda hasChart.
 */
    bool hasChart(const QString &title);
    /**
 * @brief Metoda changeChartType.
 */
    void changeChartType(const QString &chartTitle, const QString &typeName);
    /**
 * @brief Metoda getChartTitles.
 */
    QStringList getChartTitles() const;
    /**
 * @brief Metoda setChartColor.
 */
    void setChartColor(const QString &chartTitle, const QColor &color);
    /**
 * @brief Metoda setChartStyle.
 */
    void setChartStyle(const QString &chartTitle, Qt::PenStyle style, int width);

private:
    QVBoxLayout *layout;
    QMap<QString, SensorChart*> charts; // Przechowuje dynamiczne wykresy
};

#endif // CHARTWIDGET_H
