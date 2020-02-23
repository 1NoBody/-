#include "tcpsocketClient.h"
#include "websocketServer.h"


#include <QHostAddress>
#include <QProcess>
#include <QByteArray>
#include <QApplication>
#include <QCoreApplication>
#include <QDir>

QTcpSocket *TcpsocketClient::socket = new QTcpSocket;

TcpsocketClient::TcpsocketClient():isConnected(false), ip("127.0.0.1"), port(10086)
{
    connect(socket, &QTcpSocket::readyRead, this, &TcpsocketClient::recv);
    connect(socket, &QTcpSocket::connected, this, &TcpsocketClient::connected);
    //connect(socket, &QTcpSocket::connected, pTray, &SystemTray::connectMessage);
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(disconnect(QAbstractSocket::SocketError)));
    //connect(socket, &QTcpSocket::disconnected, pTray, &SystemTray::disconnectMessage);

    pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &TcpsocketClient::newConnect);
}

TcpsocketClient::~TcpsocketClient()
{

}

QTcpSocket *TcpsocketClient::getSocket()
{
    return socket;
}

void TcpsocketClient::newConnect()
{
    QProcess p;
    p.start("cmd", QStringList() << "/c" << "cmd.bat");
    p.waitForFinished();
    //qDebug() << QString::fromLocal8Bit(p.readAllStandardOutput()); //打印cmd执行结果


    socket->abort();
    socket->connectToHost(QHostAddress(ip), port);
}

bool TcpsocketClient::checkConnection()
{
    return isConnected;
}

void TcpsocketClient::bindServer(QString ip, quint16 port)
{
    this->ip = ip;
    this->port = port;
}


void TcpsocketClient::recv()
{
    QByteArray byteArray;
    byteArray.append(socket->readAll());
    QString str = QString::fromUtf8(byteArray.data());
    qDebug() << "recv from 认证机:" << str;

    QWebSocket *s = WebsocketServer::getWebSocket();
    if (s != nullptr)
        s->sendTextMessage(str);
}

void TcpsocketClient::connected()
{
    isConnected = true;
    pTimer->stop();
}

void TcpsocketClient::disconnect(QAbstractSocket::SocketError)
{
    isConnected = false;
    pTimer->start(1000);
}
