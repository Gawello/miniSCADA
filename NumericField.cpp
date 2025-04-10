#include "NumericField.h"

NumericField::NumericField() {
    label = new QLabel("0.0");
    label->setStyleSheet("font-size: 16px; padding: 5px; border: 1px solid #ccc;");
}

void NumericField::updateValue(const QVariant &value) {
    label->setText(QString::number(value.toDouble(), 'f', 2));
}

QWidget* NumericField::getWidget() {
    return label;
}
