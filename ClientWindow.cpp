#include "ClientWindow.h"
#include "ChartEditorDialog.h"
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
    qDebug() << "[ClientWindow] Otwieranie okna ustawień";

    QStringList unusedSensors = getUnusedSensors();
    QStringList existingCharts = chartWidget->getChartTitles();

    SettingsDialog dialog(unusedSensors, existingCharts, chartWidget, this);

    if (dialog.exec() == QDialog::Accepted) {
        qDebug() << "[ClientWindow] OK kliknięte w ustawieniach";

        QStringList newSensors = dialog.getSelectedSensors();
        int interval = dialog.getUpdateInterval();

        qDebug() << "[ClientWindow] Nowe sensory:" << newSensors;

        // Dodaj nowe czujniki jako wykresy z domyślnym zakresem i typem
        for (const QString &sensor : newSensors) {
            if (!sensor.isEmpty() && !chartWidget->hasChart(sensor)) {
                qDebug() << "[ClientWindow] Dodaję nowy wykres:" << sensor;
                chartWidget->addChart(sensor, 0, 100);  // domyślny zakres Y
                // Typ wykresu i styl zostaną ustawione później przez użytkownika w ChartEditorDialog
            }
        }

        // Ustaw nowy interwał odświeżania
        tcpClient->setUpdateInterval(interval);
        qDebug() << "[ClientWindow] Interwał odświeżania ustawiony na:" << interval;
    } else {
        qDebug() << "[ClientWindow] Anulowano okno ustawień";
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

void ClientWindow::openChartEditor() {
    ChartEditorDialog *editor = new ChartEditorDialog(chartWidget->getChartTitles(), this);
    connect(editor, &ChartEditorDialog::chartUpdated, this,
            [=](const QString &title,
                const QString &type,
                const QColor &color,
                Qt::PenStyle style,
                int width,
                double minY,
                double maxY) {
                chartWidget->changeChartType(title, type);
                chartWidget->setChartColor(title, color);
                chartWidget->setChartStyle(title, style, width);
                chartWidget->setAxisRange(title, minY, maxY);
            });
    editor->exec();
}
