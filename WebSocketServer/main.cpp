#include "socketserver.h"

#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir::setCurrent(QApplication::applicationDirPath());

    SocketServer w;
    w.show();
    return a.exec();
}
