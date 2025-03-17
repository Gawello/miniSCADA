#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <QRandomGenerator>
#include <iostream>

class SensorServer : public QTcpServer {
    Q_OBJECT

public:
    SensorServer(QObject *parent = nullptr) : QTcpServer(parent) {
        if (!this->listen(QHostAddress::Any, 12345)) {
            std::cerr << "Nie można uruchomić serwera!" << std::endl;
        } else {
            std::cout << "Serwer nasłuchuje na porcie 12345..." << std::endl;
        }
    }

protected:
    void incomingConnection(qintptr socketDescriptor) override {
        QTcpSocket *clientSocket = new QTcpSocket(this);
        clientSocket->setSocketDescriptor(socketDescriptor);

        std::cout << "Nowe połączenie od: " 
                  << clientSocket->peerAddress().toString().toStdString() << std::endl;

        connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
        connect(clientSocket, &QTcpSocket::readyRead, [clientSocket]() {
            QByteArray data = clientSocket->readAll();
            std::cout << "Otrzymano od klienta: " << data.toStdString() << std::endl;
        });

        sendData(clientSocket);
    }

private:
    void sendData(QTcpSocket *clientSocket) {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, [clientSocket]() {
            if (clientSocket->state() == QAbstractSocket::ConnectedState) {
                QJsonObject jsonData;
                jsonData["temperature"] = QRandomGenerator::global()->bounded(20, 30);
                jsonData["humidity"] = QRandomGenerator::global()->bounded(40, 60);
                jsonData["pressure"] = QRandomGenerator::global()->bounded(990, 1020);

                QJsonDocument doc(jsonData);
                QByteArray bytes = doc.toJson();

                clientSocket->write(bytes);
                clientSocket->flush();
            }
        });

        timer->start(1000); // Wysyłanie danych co sekundę
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    SensorServer server;
    return a.exec();
}

#include "server.moc"
