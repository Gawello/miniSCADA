#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "DataField.h"
#include <QLabel>

class TextField : public DataField {
public:
    TextField();
    void updateValue(const QVariant &value) override;
    QWidget* getWidget() override;

private:
    QLabel *label;
};

#endif // TEXTFIELD_H
