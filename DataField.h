#ifndef DATAFIELD_H
#define DATAFIELD_H

#include <QWidget>
#include <QVariant>

class DataField {
public:
    virtual ~DataField() = default;

    virtual void updateValue(const QVariant &value) = 0;
    virtual QWidget* getWidget() = 0;
};

#endif // DATAFIELD_H
