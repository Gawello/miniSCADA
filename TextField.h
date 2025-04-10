#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "DataField.h"
#include <QLabel>

/**
 * @class TextField
 * @brief Klasa odpowiedzialna za textfield.
 */
class TextField : public DataField {
public:
    TextField();
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

#endif // TEXTFIELD_H
