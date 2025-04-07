#include "TcpClient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QRandomGenerator>

TcpClient::TcpClient(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
    simulationTimer = new QTimer(this);

    connect(socket, &QTcpSocket::readyRead, this, &TcpClient::readData);
    connect(socket, &QTcpSocket::disconnected, this, &TcpClient::startSimulation);
    connect(simulationTimer, &QTimer::timeout, this, &TcpClient::simulateData);

    connectToServer("192.168.0.203", 1234);
}

void TcpClient::connectToServer(const QString &host, int port) {
    // socket->connectToHost(host, port);
    // if (!socket->waitForConnected(5000)) {
    //     qWarning("Nie udało się połączyć z serwerem!");
    // }
    socket->connectToHost(host, port);
    if (!socket->waitForConnected(3000)) {
        qDebug() << "Brak połączenia – tryb symulacji aktywowany.";
        startSimulation();
    }
}

void TcpClient::readData() {
    while (socket->canReadLine()) {
        QByteArray data = socket->readLine().trimmed();
        emit newDataReceived(QString::fromUtf8(data));
    }
}

void TcpClient::setUpdateInterval(int interval) {
    socket->setSocketOption(QAbstractSocket::LowDelayOption, interval);
}

void TcpClient::startSimulation() {
    simulationMode = true;
    simulationTimer->start(1000); // co 1 sekunda
}

void TcpClient::simulateData() {
    QJsonObject fakeData;
    double temp    = QRandomGenerator::global()->bounded(200, 300) / 10.0; // Nie przyjmuje double
    double humidity = QRandomGenerator::global()->bounded(100, 800) / 10.0;
    double pressure = QRandomGenerator::global()->bounded(9800, 10500) / 10.0;
    double anotherdata = QRandomGenerator::global()->bounded(1,2000);

    fakeData["Temperatura (°C)"] = temp;
    fakeData["Wilgotność (%)"] = humidity;
    fakeData["Ciśnienie (hPa)"] = pressure;
    fakeData["Inne dane(j)"] = anotherdata;

    QJsonDocument doc(fakeData);
    emit newDataReceived(QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
}
