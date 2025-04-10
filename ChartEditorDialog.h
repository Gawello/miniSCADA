#ifndef CHARTEDITORDIALOG_H
#define CHARTEDITORDIALOG_H

#include <QDialog>
#include <QColor>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QtCharts/QChartView>
#include <QStringList>

class ChartEditorDialog : public QDialog {
    Q_OBJECT

public:
    explicit ChartEditorDialog(const QStringList &chartNames, QWidget *parent = nullptr);

signals:
    void chartUpdated(const QString &chartName,
                      const QString &chartType,
                      const QColor &lineColor,
                      Qt::PenStyle style,
                      int width,
                      double minY,
                      double maxY);

private:
    void updatePreview();
    void chooseColor();
    void previewChart(const QString &chartName);
    void applyChanges();

    QComboBox *chartSelector;
    QComboBox *typeSelector;
    QComboBox *lineStyleSelector;
    QSpinBox *lineWidthSpin;
    QDoubleSpinBox *minYSpin;
    QDoubleSpinBox *maxYSpin;
    QPushButton *colorButton;
    QChartView *previewView;

    QColor selectedColor = Qt::blue;
    QString currentChart;
};

#endif // CHARTEDITORDIALOG_H
