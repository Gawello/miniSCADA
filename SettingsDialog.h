#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QFormLayout>

class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog(const QStringList &availableSensors, QWidget *parent = nullptr);
    int getUpdateInterval() const;
    double getMinY() const;
    double getMaxY() const;
    QString getSelectedSensor() const; // Zwraca wybrany nowy czujnik
    QString getSelectedChartType() const;

private:
    QSpinBox *updateIntervalSpinBox;
    QDoubleSpinBox *minYSpinBox;
    QDoubleSpinBox *maxYSpinBox;
    QComboBox *sensorComboBox; // Lista dostępnych czujników
    QComboBox *chartTypeComboBox;


};

#endif // SETTINGSDIALOG_H
