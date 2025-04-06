#include "TcpClient.h"
#include <QJsonDocument>
#include <QJsonObject>

TcpClient::TcpClient(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &TcpClient::readData);
    connectToServer("192.168.1.203", 12345); // Ustaw IP Raspberry Pi
}

void TcpClient::connectToServer(const QString &host, int port) {
    socket->connectToHost(host, port);
    if (!socket->waitForConnected(5000)) {
        qWarning("Nie udało się połączyć z serwerem!");
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
