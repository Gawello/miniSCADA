#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

/**
 * @class TcpClient
 * @brief Klasa odpowiedzialna za tcpclient.
 */
class TcpClient : public QObject {
    Q_OBJECT

public:
    /**
 * @brief Metoda TcpClient.
 */
    explicit TcpClient(QObject *parent = nullptr);
    /**
 * @brief Metoda connectToServer.
 */
    void connectToServer(const QString &host, int port);
    /**
 * @brief Metoda setUpdateInterval.
 */
    void setUpdateInterval(int interval);
    /**
 * @brief Metoda connectToServer.
 */
    void connectToServer(const QString &host, quint16 port);
    /**
 * @brief Metoda startSimulation.
 */
    void startSimulation();


signals:
    /**
 * @brief Metoda newDataReceived.
 */
    void newDataReceived(const QString &data);

private slots:
    /**
 * @brief Metoda readData.
 */
    void readData();
    /**
 * @brief Metoda simulateData.
 */
    void simulateData(); // generuje dane losowe

private:
    QTcpSocket *socket;
    QTimer *simulationTimer;
    bool simulationMode = false;
};

#endif // TCPCLIENT_H
