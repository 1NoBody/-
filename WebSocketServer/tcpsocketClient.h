#ifndef TCPSOCKETCLIENT_H
#define TCPSOCKETCLIENT_H

#include <QTcpSocket>
#include <QTimer>

class TcpsocketClient : public QObject
{
    Q_OBJECT
public:
    TcpsocketClient();
    ~TcpsocketClient();

    static QTcpSocket *getSocket();
    void newConnect();
    bool checkConnection();
    void bindServer(QString ip = "127.0.0.1", quint16 port = 10086);

private:
    static QTcpSocket *socket;
    bool isConnected;
    QString ip;
    quint16 port;
    QTimer *pTimer;


private slots:
    void recv();
    void connected();
    void disconnect(QAbstractSocket::SocketError);
};

#endif // TCPSOCKETCLIENT_H
