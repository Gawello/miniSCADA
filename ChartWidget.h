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
    void addChart(const QString &title, double minY=0, double maxY=100);
    void addData(const QString &chartTitle, double value);
    void clearAllCharts();
    void saveToCSV(const QString &filePath);
    void setAxisRange(const QString &chartTitle, double minY=0, double maxY=100);
    bool hasChart(const QString &title);
    void changeChartType(const QString &chartTitle, const QString &typeName);
    QStringList getChartTitles() const;
    void setChartColor(const QString &chartTitle, const QColor &color);
    void setChartStyle(const QString &chartTitle, Qt::PenStyle style, int width);

private:
    QVBoxLayout *layout;
    QMap<QString, SensorChart*> charts; // Przechowuje dynamiczne wykresy
};

#endif // CHARTWIDGET_H
