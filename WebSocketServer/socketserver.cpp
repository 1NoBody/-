#include "socketserver.h"
#include <QApplication>
#include <QEvent>
#include <QCloseEvent>


SocketServer::SocketServer(QWidget *parent)
    : QWidget(parent)
{
    /* 窗口属性 */
    this->resize(400, 200);
    this->setFixedSize(this->size());
    this->setWindowIcon(QIcon(":/32.ico"));

    /* 控件 */
    pIp_label = new QLabel(this);
    pIp_label->setGeometry(60, 30, 80, 30);
    pIp_label->setText(QString::fromUtf8("认证机IP"));

    pIp_edit = new QLineEdit(this);
    pIp_edit->setGeometry(150, 30, 130, 30);
    pIp_edit->setText("127.0.0.1");

    pPort_label = new QLabel(this);
    pPort_label->setGeometry(60, 80, 80, 30);
    pPort_label->setText(QString::fromUtf8("认证机端口"));

    pPort_edit = new QLineEdit(this);
    pPort_edit->setGeometry(150, 80, 130, 30);
    pPort_edit->setText("10086");

    pConnect_button = new QPushButton(this);
    pConnect_button->setGeometry(this->geometry().width()/2 - 50, 130, 100, 30);
    pConnect_button->setText(QString::fromUtf8("连接"));
    connect(pConnect_button, &QPushButton::clicked, this, &SocketServer::connectEvent);

    pCheckConnection_label = new QLabel(this);
    pCheckConnection_label->setGeometry(this->geometry().width()/2 - 100, 130, 200, 30);
    pCheckConnection_label->setAlignment(Qt::AlignCenter);
    pCheckConnection_label->hide();


    /* 初始化 */
    pServer = new WebsocketServer;
    pServer->setParent(this);

    pClient = new TcpsocketClient();
    pClient->setParent(this);
    //pClient->bindServer(pIp_edit->text(), pPort_edit->text().toUShort());

    pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &SocketServer::timeout);
    //pTimer->start(1000);

    pTray = new SystemTray(this);
    //pTray->setParent(this);

}

SocketServer::~SocketServer()
{
}

void SocketServer::connectEvent()
{
    pIp_edit->setEnabled(false);
    pPort_edit->setEnabled(false);
    pConnect_button->hide();
    pCheckConnection_label->show();
    pClient->bindServer(pIp_edit->text(), pPort_edit->text().toUShort());
    pClient->newConnect();
    pTimer->start(500);
}

void SocketServer::timeout()
{
    if (pClient->checkConnection())
        pCheckConnection_label->setText(QString::fromUtf8("当前状态：已连接"));
    else
        pCheckConnection_label->setText(QString::fromUtf8("当前状态：未连接"));
}

void SocketServer::resume()
{
    this->show();
}


void SocketServer::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
}

