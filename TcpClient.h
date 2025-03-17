#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

class TcpClient : public QObject {
    Q_OBJECT

public:
    explicit TcpClient(QObject *parent = nullptr);
    void connectToServer(const QString &host, int port);
    void setUpdateInterval(int interval);


signals:
    void newDataReceived(const QString &data);

private slots:
    void readData();

private:
    QTcpSocket *socket;
};

#endif // TCPCLIENT_H
