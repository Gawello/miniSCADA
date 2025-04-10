#ifndef SENSORSELECTIONDIALOG_H
#define SENSORSELECTIONDIALOG_H

#include <QDialog>
#include <QMap>
#include <QCheckBox>
#include <QStringList>

/**
 * @class SensorSelectionDialog
 * @brief Klasa odpowiedzialna za sensorselectiondialog.
 */
class SensorSelectionDialog : public QDialog {
    Q_OBJECT

public:
    /**
 * @brief Metoda SensorSelectionDialog.
 */
    explicit SensorSelectionDialog(const QStringList &availableSensors, QWidget *parent = nullptr);
    /**
 * @brief Metoda getSelectedSensors.
 */
    QStringList getSelectedSensors() const;

private:
    QMap<QString, QCheckBox*> checkboxes;
};

#endif // SENSORSELECTIONDIALOG_H
