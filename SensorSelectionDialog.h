#ifndef SENSORSELECTIONDIALOG_H
#define SENSORSELECTIONDIALOG_H

#include <QDialog>
#include <QMap>
#include <QCheckBox>
#include <QStringList>

class SensorSelectionDialog : public QDialog {
    Q_OBJECT

public:
    explicit SensorSelectionDialog(const QStringList &availableSensors, QWidget *parent = nullptr);
    QStringList getSelectedSensors() const;

private:
    QMap<QString, QCheckBox*> checkboxes;
};

#endif // SENSORSELECTIONDIALOG_H
