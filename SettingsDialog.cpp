#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(const QStringList &availableSensors, QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Ustawienia");

    QFormLayout *layout = new QFormLayout(this);

    updateIntervalSpinBox = new QSpinBox(this);
    updateIntervalSpinBox->setRange(100, 5000);
    updateIntervalSpinBox->setValue(1000);

    minYSpinBox = new QDoubleSpinBox(this);
    minYSpinBox->setRange(-1000, 1000);
    minYSpinBox->setValue(0);

    maxYSpinBox = new QDoubleSpinBox(this);
    maxYSpinBox->setRange(-1000, 1000);
    maxYSpinBox->setValue(100);

    sensorComboBox = new QComboBox(this);
    sensorComboBox->addItems(availableSensors);

    layout->addRow("Interwał odświeżania (ms):", updateIntervalSpinBox);
    layout->addRow("Minimalna wartość Y:", minYSpinBox);
    layout->addRow("Maksymalna wartość Y:", maxYSpinBox);
    layout->addRow("Nowy czujnik do dodania:", sensorComboBox);

    QPushButton *okButton = new QPushButton("OK", this);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    layout->addWidget(okButton);
}

int SettingsDialog::getUpdateInterval() const {
    return updateIntervalSpinBox->value();
}

double SettingsDialog::getMinY() const {
    return minYSpinBox->value();
}

double SettingsDialog::getMaxY() const {
    return maxYSpinBox->value();
}

QString SettingsDialog::getSelectedSensor() const {
    return sensorComboBox->currentText();
}
