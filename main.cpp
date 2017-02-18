#include "mainwindow.h"
#include <QApplication>

#include "SocketCommunicators/test_socketcommunicators.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    TestSignalGenerator();

    return a.exec();
}
