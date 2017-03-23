#ifndef TESTPANELS_H
#define TESTPANELS_H

//C System-Headers
//
//C++ System headers
#include <memory>
//Qt Headers
#include <QTimer>
#include <QObject>
#include <QApplication>
//OpenCV Headers
//
//Boost Headers
//
//Project specific headers
#include "Digitizer/ATS9462Engine/ats9462engine.h"
#include "../Windows/mainwindow.h"
#include "SpectrumAnalyzer/spectrumanalyzer.h"
#include "../SocketCommunicators/NetworkAnalyzer/network_analyzer.h"
#include "../Windows/mainwindow.h"
#include "InstrumentView/instrumentview.h"

namespace etig {

namespace test {

class
    TestPanels {

  public:
    void Test();

  private:
    MainWindow* w;
    SpectrumAnalyzer* spec;

    std::shared_ptr<ATS9462Engine> digitizer;

    InstrumentView* na_view;
    std::shared_ptr<NetworkAnalyzer> hp8757_c;

};

}

}

#endif // TESTPANELS_HH
