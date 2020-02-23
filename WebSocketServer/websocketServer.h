#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QWebSocket>
#include <QWebSocketServer>

class WebsocketServer : public QObject
{
    Q_OBJECT

public:
    WebsocketServer(quint16 port = 8124 , QObject *parent = nullptr);
    ~WebsocketServer();

    static QWebSocket *getWebSocket();
private:
    QWebSocketServer *server;
    static QWebSocket *pSocket;

    bool isConnected; //单客户端控制
private slots:
    void newConnection();
    void recv(QString message);
    void abortConnection();

};

#endif // WEBSOCKETSERVER_H
