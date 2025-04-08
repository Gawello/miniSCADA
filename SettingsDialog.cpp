#include "SettingsDialog.h"
#include "ChartEditorDialog.h"

SettingsDialog::SettingsDialog::SettingsDialog(const QStringList &availableSensors,
                                               const QStringList &existingCharts,
                                               ChartWidget *chartWidgetRef,
                                               QWidget *parent)
    : QDialog(parent),
    chartWidget(chartWidgetRef) {
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
    sensorComboBox->addItem(" ");
    sensorComboBox->addItems(availableSensors);

    layout->addRow("Interwał odświeżania (ms):", updateIntervalSpinBox);
    layout->addRow("Minimalna wartość Y:", minYSpinBox);
    layout->addRow("Maksymalna wartość Y:", maxYSpinBox);
    layout->addRow("Nowy czujnik do dodania:", sensorComboBox);

    editChartComboBox = new QComboBox(this);
    editChartComboBox->addItem(" ");
    editChartComboBox->addItems(existingCharts);
    layout->addRow("Edytuj wykres:", editChartComboBox);

    QPushButton *editChartsBtn = new QPushButton("Edytuj wykresy", this);
    QPushButton *editPanelsBtn = new QPushButton("Edytuj pola danych", this);
    QPushButton *editControlsBtn = new QPushButton("Edytuj kontrolki", this);

    layout->addWidget(editChartsBtn);
    layout->addWidget(editPanelsBtn);
    layout->addWidget(editControlsBtn);

    connect(editChartsBtn, &QPushButton::clicked, this, [this]() {
        ChartEditorDialog *dialog = new ChartEditorDialog(chartWidget->getChartTitles(), this);
        dialog->exec();
    });
    connect(editChartsBtn, &QPushButton::clicked, this, [this]() {
        ChartEditorDialog *dialog = new ChartEditorDialog(chartWidget->getChartTitles(), this);
        dialog->exec();
    });

    chartTypeComboBox = new QComboBox(this);
    chartTypeComboBox->addItems({"Line", "Scatter"});
    layout->addRow("Typ wykresu:", chartTypeComboBox);

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

QString SettingsDialog::getSelectedChartType() const {
    return chartTypeComboBox->currentText();
}

QString SettingsDialog::getChartToEdit() const {
    return editChartComboBox->currentText();
}


