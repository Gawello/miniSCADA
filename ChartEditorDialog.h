#ifndef CHARTEDITORDIALOG_H
#define CHARTEDITORDIALOG_H

#include <QDialog>
#include <QColor>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QtCharts/QChartView>
#include <QStringList>

/**
 * @class ChartEditorDialog
 * @brief Klasa odpowiedzialna za charteditordialog.
 */
class ChartEditorDialog : public QDialog {
    Q_OBJECT

public:
    /**
 * @brief Metoda ChartEditorDialog.
 */
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
    /**
 * @brief Metoda updatePreview.
 */
    void updatePreview();
    /**
 * @brief Metoda chooseColor.
 */
    void chooseColor();
    /**
 * @brief Metoda previewChart.
 */
    void previewChart(const QString &chartName);
    /**
 * @brief Metoda applyChanges.
 */
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
