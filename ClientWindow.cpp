#include "ClientWindow.h"
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileDialog>

ClientWindow::ClientWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Mini SCADA - Klient");
    resize(800, 600);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    chartWidget = new ChartWidget(this);

    // Dodaje domyślne wykresy
    chartWidget->addChart("Temperatura (°C)", 0, 50);
    chartWidget->addChart("Wilgotność (%)", 0, 100);
    chartWidget->addChart("Ciśnienie (hPa)", 900, 1100);

    knownSensors.insert("Temperatura (°C)");
    knownSensors.insert("Wilgotność (%)");
    knownSensors.insert("Ciśnienie (hPa)");

    saveButton = new QPushButton("Zapisz do CSV", this);
    connect(saveButton, &QPushButton::clicked, this, &ClientWindow::saveCSV);

    settingsButton = new QPushButton("Ustawienia", this);
    connect(settingsButton, &QPushButton::clicked, this, &ClientWindow::openSettings);

    layout->addWidget(chartWidget);
    layout->addWidget(saveButton);
    layout->addWidget(settingsButton);
    setCentralWidget(centralWidget);

    tcpClient = new TcpClient(this);
    connect(tcpClient, &TcpClient::newDataReceived, this, &ClientWindow::updateData);
}

ClientWindow::~ClientWindow() {}

void ClientWindow::updateData(const QString &data) {
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    if (!doc.isObject()) return;

    QJsonObject obj = doc.object();

    for (const QString &key : obj.keys()) {
        double value = obj[key].toDouble();

        if (!knownSensors.contains(key)) {
            knownSensors.insert(key); // Zapisuje nowy czujnik
        }

        chartWidget->addData(key, value);
    }
}

void ClientWindow::saveCSV() {
    QString filePath = QFileDialog::getSaveFileName(this, "Zapisz jako", "", "CSV (*.csv)");
    if (!filePath.isEmpty()) {
        chartWidget->saveToCSV(filePath);
    }
}

void ClientWindow::openSettings() {
    QStringList unusedSensors = getUnusedSensors();
    QStringList existingCharts = chartWidget->getChartTitles(); // nowa metoda

    SettingsDialog dialog(unusedSensors, existingCharts, this);

    if (dialog.exec() == QDialog::Accepted) {
        QString chartToEdit = dialog.getChartToEdit();        // istniejący wykres
        QString newSensor = dialog.getSelectedSensor();       // nowy czujnik
        QString chartType = dialog.getSelectedChartType();
        double minY = dialog.getMinY();
        double maxY = dialog.getMaxY();
        int interval = dialog.getUpdateInterval();

        if (!newSensor.isEmpty() && !chartWidget->hasChart(newSensor)) {
            chartWidget->addChart(newSensor, minY, maxY);
            chartWidget->changeChartType(newSensor, chartType);
        }

        if (!chartToEdit.isEmpty()) {
            chartWidget->setAxisRange(chartToEdit, minY, maxY);
            chartWidget->changeChartType(chartToEdit, chartType);
        }

        tcpClient->setUpdateInterval(interval);
    }
}

QStringList ClientWindow::getUnusedSensors() const {
    QStringList unused;
    for (const QString &sensor : knownSensors) {
        if (!chartWidget->hasChart(sensor)) {
            unused.append(sensor);
        }
    }
    return unused;
}
