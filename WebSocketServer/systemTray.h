#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H


#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>

class SystemTray : public QWidget
{
    Q_OBJECT
public:
    SystemTray(QWidget *parent = nullptr);
    ~SystemTray();

    //static QSystemTrayIcon *getTray();

private:
    QSystemTrayIcon *tray;
    QMenu *menu;
    QAction *resumeAction;
    QAction *quitAction;

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
public slots:
    void connectMessage();
    void disconnectMessage();
};

#endif // SYSTEMTRAY_H
