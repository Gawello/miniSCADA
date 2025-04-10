#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QStringList>
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
    QStringList getSelectedSensors() const;

private:
    QSpinBox *updateIntervalSpinBox = nullptr;
    QStringList availableSensors;
    QStringList selectedSensors;

    ChartWidget *chartWidget = nullptr;
};

#endif // SETTINGSDIALOG_H
