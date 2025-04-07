#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include "SensorChart.h"

class ChartWidget : public QWidget {
    Q_OBJECT

public:
    explicit ChartWidget(QWidget *parent = nullptr);
    void addChart(const QString &title, double minY, double maxY);
    void addData(const QString &chartTitle, double value);
    void clearAllCharts();
    void saveToCSV(const QString &filePath);
    void setAxisRange(double minY, double maxY);
    bool hasChart(const QString &title);
    void changeChartType(const QString &chartTitle, const QString &typeName);


private:
    QVBoxLayout *layout;
    QMap<QString, SensorChart*> charts; // Przechowuje dynamiczne wykresy
};

#endif // CHARTWIDGET_H
