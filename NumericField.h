#ifndef NUMERICFIELD_H
#define NUMERICFIELD_H

#include "DataField.h"
#include <QLabel>

class NumericField : public DataField {
public:
    NumericField();
    void updateValue(const QVariant &value) override;
    QWidget* getWidget() override;

private:
    QLabel *label;
};

#endif // NUMERICFIELD_H
