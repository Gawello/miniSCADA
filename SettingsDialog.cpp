#include "SettingsDialog.h"
#include "ChartEditorDialog.h"


SettingsDialog::SettingsDialog(const QStringList &availableSensors,
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

    layout->addRow("Interwał odświeżania (ms):", updateIntervalSpinBox);

    this->availableSensors = availableSensors;
    QPushButton *selectSensorsButton = new QPushButton("Wybierz czujniki do dodania", this);
    layout->addRow("Nowe czujniki:", selectSensorsButton);

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

    connect(selectSensorsButton, &QPushButton::clicked, this, [this]() {
        SensorSelectionDialog dialog(this->availableSensors, this);
        if (dialog.exec() == QDialog::Accepted) {
            selectedSensors = dialog.getSelectedSensors();
        }
    });


    QPushButton *okButton = new QPushButton("OK", this);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    layout->addWidget(okButton);
}

int SettingsDialog::getUpdateInterval() const {
    int val = updateIntervalSpinBox ? updateIntervalSpinBox->value() : 1000;
    qDebug() << "[SettingsDialog] getUpdateInterval():" << val;
    return val;
}

QStringList SettingsDialog::getSelectedSensors() const {
    qDebug() << "[SettingsDialog] getSelectedSensors():" << selectedSensors;
    return selectedSensors;
}

QString SettingsDialog::getSelectedChartType() const {
    if (!chartTypeComboBox) {
        qDebug() << "[SettingsDialog] chartTypeComboBox == nullptr!";
        return "Line"; // fallback
    }

    QString val = chartTypeComboBox->currentText();
    qDebug() << "[SettingsDialog] getSelectedChartType():" << val;
    return val;
}


QString SettingsDialog::getChartToEdit() const {
    if (editChartComboBox->currentText() == " "){
        qDebug() << "Jest pusto!";
        return QString();
    }
    auto value = editChartComboBox ? editChartComboBox->currentText() : QString();

    qDebug() << "[SettingsDialog] getChartToEdit():" << value;
    return value;
}

