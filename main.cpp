#include "mainwindow.h"
#include <QApplication>

#include "ModeCharacterization/test_modecharacterization.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    TestModeCharacterization();

    return a.exec();
}
