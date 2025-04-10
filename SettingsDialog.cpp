#include "SettingsDialog.h"
#include "ChartEditorDialog.h"

SettingsDialog::SettingsDialog(const QStringList &availableSensors,
                               const QStringList &existingCharts,
                               ChartWidget *chartWidgetRef,
                               QWidget *parent)
    : QDialog(parent), availableSensors(availableSensors), chartWidget(chartWidgetRef) {

    setWindowTitle("Ustawienia");

    QFormLayout *layout = new QFormLayout(this);

    updateIntervalSpinBox = new QSpinBox(this);
    updateIntervalSpinBox->setRange(100, 5000);
    updateIntervalSpinBox->setValue(1000);
    layout->addRow("Interwał odświeżania (ms):", updateIntervalSpinBox);

    // Wybór czujników do dodania
    QPushButton *selectSensorsButton = new QPushButton("Wybierz czujniki do dodania", this);
    layout->addRow("Nowe czujniki:", selectSensorsButton);

    connect(selectSensorsButton, &QPushButton::clicked, this, [this]() {
        SensorSelectionDialog dialog(this->availableSensors, this);
        if (dialog.exec() == QDialog::Accepted) {
            selectedSensors = dialog.getSelectedSensors();
        }
    });

    // Przyciski do edycji
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

    // Przycisk OK
    QPushButton *okButton = new QPushButton("OK", this);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    layout->addWidget(okButton);
}

int SettingsDialog::getUpdateInterval() const {
    return updateIntervalSpinBox ? updateIntervalSpinBox->value() : 1000;
}

QStringList SettingsDialog::getSelectedSensors() const {
    return selectedSensors;
}
