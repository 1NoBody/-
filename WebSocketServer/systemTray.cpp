#include "systemTray.h"
#include "tcpsocketClient.h"

#include <QCoreApplication>
#include <QApplication>
#include <QIcon>


//QSystemTrayIcon *SystemTray::tray = new QSystemTrayIcon;

SystemTray::SystemTray(QWidget *parent)
    :QWidget(parent)
{
    resumeAction = new QAction(QString::fromUtf8("显示主窗口"), this);
    connect(resumeAction, &QAction::triggered, parent, &QWidget::show);
    quitAction = new QAction(QString::fromUtf8("退出"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    menu = new QMenu(this);
    menu->addAction(resumeAction);
    menu->addSeparator();
    menu->addAction(quitAction);

    tray = new QSystemTrayIcon(this);
    connect(tray, &QSystemTrayIcon::activated, this, &SystemTray::iconActivated);
    QIcon icon(":/32.ico");
    tray->setIcon(icon);
    tray->setToolTip(QString::fromUtf8("中间件插件"));
    tray->setContextMenu(menu);
    tray->show();

    connect(TcpsocketClient::getSocket(), &QTcpSocket::connected, this, &SystemTray::connectMessage);
    connect(TcpsocketClient::getSocket(), &QTcpSocket::disconnected, this, &SystemTray::disconnectMessage);
}

SystemTray::~SystemTray()
{

}

void SystemTray::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            this->parentWidget()->show();
            break;
        default:
            break;
    }
}

void SystemTray::connectMessage()
{
    tray->showMessage(QString::fromUtf8("温馨提示"), QString::fromUtf8("认证机连接成功"), QSystemTrayIcon::MessageIcon::Information, 2000);
}

void SystemTray::disconnectMessage()
{
    tray->showMessage(QString::fromUtf8("温馨提示"), QString::fromUtf8("认证机连接中断"), QSystemTrayIcon::MessageIcon::Information, 2000);
}

