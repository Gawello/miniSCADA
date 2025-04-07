#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

class TcpClient : public QObject {
    Q_OBJECT

public:
    explicit TcpClient(QObject *parent = nullptr);
    void connectToServer(const QString &host, int port);
    void setUpdateInterval(int interval);
    void connectToServer(const QString &host, quint16 port);
    void startSimulation();


signals:
    void newDataReceived(const QString &data);

private slots:
    void readData();
    void simulateData(); // generuje dane losowe

private:
    QTcpSocket *socket;
    QTimer *simulationTimer;
    bool simulationMode = false;
};

#endif // TCPCLIENT_H
