#ifndef CHARTEDITORDIALOG_H
#define CHARTEDITORDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QColor>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>

QT_BEGIN_NAMESPACE
namespace QtCharts {
class QChart;
}
QT_END_NAMESPACE

class ChartEditorDialog : public QDialog {
    Q_OBJECT

public:
    explicit ChartEditorDialog(const QStringList &chartNames,
                               QWidget *parent = nullptr);

signals:
    void chartUpdated(const QString &chartName,
                      const QString &chartType,
                      const QColor &lineColor,
                      Qt::PenStyle style,
                      int width,
                      double minY,
                      double maxY);

private slots:
    void chooseColor();
    void applyChanges();
    void previewChart(const QString &chartName);

private:
    QComboBox *chartSelector;
    QComboBox *typeSelector;
    QPushButton *colorButton;
    QDoubleSpinBox *minYSpin;
    QDoubleSpinBox *maxYSpin;
    QChartView *previewView;

    QColor selectedColor = Qt::blue;
    QString currentChart;
    QComboBox *lineStyleSelector;
    QSpinBox *lineWidthSpin;

    void updatePreview();
};

#endif // CHARTEDITORDIALOG_H
