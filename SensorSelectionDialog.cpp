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

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &SensorSelectionDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SensorSelectionDialog::reject);
}

QStringList SensorSelectionDialog::getSelectedSensors() const {
    QStringList selected;
    for (const auto &key : checkboxes.keys()) {
        if (checkboxes[key]->isChecked())
            selected.append(key);
    }
    return selected;
}
