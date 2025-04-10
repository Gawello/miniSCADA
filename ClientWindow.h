#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "TcpClient.h"
#include "ChartWidget.h"
#include "SettingsDialog.h"

/**
 * @class ClientWindow
 * @brief Klasa odpowiedzialna za clientwindow.
 */
class ClientWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
 * @brief Metoda ClientWindow.
 */
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();
    /**
 * @brief Metoda openChartEditor.
 */
    void openChartEditor();

private slots:
    /**
 * @brief Metoda updateData.
 */
    void updateData(const QString &data);
    /**
 * @brief Metoda saveCSV.
 */
    void saveCSV();
    /**
 * @brief Metoda openSettings.
 */
    void openSettings();
    /**
 * @brief Metoda getUnusedSensors.
 */
    QStringList getUnusedSensors() const;

private:
    TcpClient *tcpClient;
    ChartWidget *chartWidget;
    QPushButton *saveButton;
    QPushButton *settingsButton;
    QSet<QString> knownSensors;
};

#endif // CLIENTWINDOW_H
