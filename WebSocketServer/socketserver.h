#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include "websocketServer.h"
#include "tcpsocketClient.h"
#include "systemTray.h"


#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>

class SocketServer : public QWidget
{
    Q_OBJECT

public:
    SocketServer(QWidget *parent = nullptr);
    ~SocketServer();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    QLabel *pIp_label;
    QLineEdit *pIp_edit;
    QLabel *pPort_label;
    QLineEdit *pPort_edit;
    QPushButton *pConnect_button;
    QLabel *pCheckConnection_label;

    QTimer *pTimer;

    WebsocketServer *pServer;
    TcpsocketClient *pClient;
    SystemTray *pTray;

private slots:
    void connectEvent();
    void timeout();
    void resume();
};
#endif // SOCKETSERVER_H
