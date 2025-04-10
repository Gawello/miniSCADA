#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QStringList>
#include "ChartWidget.h"
#include "SensorSelectionDialog.h"

/**
 * @class SettingsDialog
 * @brief Klasa odpowiedzialna za settingsdialog.
 */
class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog(const QStringList &availableSensors,
                            const QStringList &existingCharts,
                            ChartWidget *chartWidgetRef,
                            QWidget *parent = nullptr);

    /**
 * @brief Metoda getUpdateInterval.
 */
    int getUpdateInterval() const;
    /**
 * @brief Metoda getSelectedSensors.
 */
    QStringList getSelectedSensors() const;

signals:
    void chartUpdated(const QString &chartName,
                      const QString &chartType,
                      const QColor &lineColor,
                      Qt::PenStyle style,
                      int width,
                      double minY,
                      double maxY);

private:
    QSpinBox *updateIntervalSpinBox = nullptr;
    QStringList availableSensors;
    QStringList selectedSensors;

    ChartWidget *chartWidget = nullptr;
};

#endif // SETTINGSDIALOG_H
