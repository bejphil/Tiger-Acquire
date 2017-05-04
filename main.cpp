//C System-Headers
//
//C++ System headers
//
// Qt
//#include "Windows/mainwindow.h"
#include <QApplication>
#include <QObject>
#include <QThread>
// Project specific headers
#include "ModeCharacterization/test_modecharacterization.h"
#include "Program/Program/program.h"
#include "Panels/testpanels.h"

#include "Windows/mainwindow.h"
#include "Panels/SpectrumAnalyzer/spectrumanalyzer.h"
#include "Windows/mainwindow.h"
#include "Panels/InstrumentView/instrumentview.h"

#include "Algorithm/algorithm_test.h"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    QApplication q_app(argc, argv);
    MainWindow window;

    return q_app.exec();

}
