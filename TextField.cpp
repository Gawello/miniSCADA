#include "TextField.h"

TextField::TextField() {
    label = new QLabel("brak danych");
    label->setStyleSheet("font-style: italic; padding: 5px;");
}

void TextField::updateValue(const QVariant &value) {
    label->setText(value.toString());
}

QWidget* TextField::getWidget() {
    return label;
}
