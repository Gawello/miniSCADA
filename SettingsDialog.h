#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QFormLayout>
#include "ChartWidget.h"
#include "SensorSelectionDialog.h"

class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog(const QStringList &availableSensors,
                            const QStringList &existingCharts,
                            ChartWidget *chartWidgetRef,
                            QWidget *parent = nullptr);
    int getUpdateInterval() const;
    QStringList getSelectedSensors() const; // Zwraca wybrany nowy czujnik
    QString getSelectedChartType() const;
    QComboBox *editChartComboBox;
    QString getChartToEdit() const;

private:
    QSpinBox *updateIntervalSpinBox;
    // QComboBox *sensorComboBox; // Lista dostępnych czujników
    QComboBox *chartTypeComboBox;
    ChartWidget *chartWidget;
    QStringList selectedSensors;
    QStringList availableSensors;


};

#endif // SETTINGSDIALOG_H
