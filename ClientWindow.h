#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "TcpClient.h"
#include "ChartWidget.h"
#include "SettingsDialog.h"

class ClientWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();
    void openChartEditor();

private slots:
    void updateData(const QString &data);
    void saveCSV();
    void openSettings();
    QStringList getUnusedSensors() const;

private:
    TcpClient *tcpClient;
    ChartWidget *chartWidget;
    QPushButton *saveButton;
    QPushButton *settingsButton;
    QSet<QString> knownSensors;
};

#endif // CLIENTWINDOW_H
