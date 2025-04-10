#ifndef NUMERICFIELD_H
#define NUMERICFIELD_H

#include "DataField.h"
#include <QLabel>

/**
 * @class NumericField
 * @brief Klasa odpowiedzialna za numericfield.
 */
class NumericField : public DataField {
public:
    NumericField();
    /**
 * @brief Metoda updateValue.
 */
    void updateValue(const QVariant &value) override;
    /**
 * @brief Metoda getWidget.
 */
    QWidget* getWidget() override;

private:
    QLabel *label;
};

#endif // NUMERICFIELD_H
