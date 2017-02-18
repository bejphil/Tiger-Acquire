#include "mainwindow.h"
#include <QApplication>

#include "SocketCommunicators/test_socketcommunicators.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    test_socket_comm();

    return a.exec();
}
