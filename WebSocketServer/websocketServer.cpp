#include "websocketServer.h"
#include "tcpsocketClient.h"

#include <qdebug.h>

QWebSocket *WebsocketServer::pSocket = nullptr;

WebsocketServer::WebsocketServer(quint16 port, QObject *parent)
    :QObject(parent), isConnected(false)
{
    server = new QWebSocketServer("server", QWebSocketServer::NonSecureMode);
    connect(server, &QWebSocketServer::newConnection, this, &WebsocketServer::newConnection);
    server->listen(QHostAddress::Any, port);
    //qDebug() << "listen start";
}

WebsocketServer::~WebsocketServer()
{

}

QWebSocket *WebsocketServer::getWebSocket()
{
    return pSocket;
}

void WebsocketServer::newConnection()
{
    if (isConnected)
        return;

    isConnected = true;
    pSocket = server->nextPendingConnection();
    connect(pSocket, &QWebSocket::textMessageReceived, this, &WebsocketServer::recv);
    connect(pSocket, &QWebSocket::disconnected, this, &WebsocketServer::abortConnection);
    //qDebug() << "new connection";
}

void WebsocketServer::recv(QString message)
{
    //qDebug() << "recv:" << message;
    //pSocket->sendTextMessage(message); //test

    QTcpSocket *s = TcpsocketClient::getSocket();
    s->write(message.toStdString().c_str());
}

void WebsocketServer::abortConnection()
{
    pSocket->deleteLater(); //TBD
    pSocket = nullptr;
    isConnected = false;
    //qDebug() << "disconnected";
}
