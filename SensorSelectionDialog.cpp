#include "SensorSelectionDialog.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>

SensorSelectionDialog::SensorSelectionDialog(const QStringList &availableSensors, QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Wybierz czujniki do dodania");

    QVBoxLayout *layout = new QVBoxLayout(this);
    for (const QString &sensor : availableSensors) {
        QCheckBox *box = new QCheckBox(sensor, this);
        checkboxes[sensor] = box;
        layout->addWidget(box);
    }

    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SensorSelectionDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SensorSelectionDialog::reject);
    layout->addWidget(buttonBox);
}

QStringList SensorSelectionDialog::getSelectedSensors() const {
    QStringList selected;
    for (const auto &key : checkboxes.keys()) {
        if (checkboxes[key]->isChecked())
            selected.append(key);
    }
    return selected;
}
