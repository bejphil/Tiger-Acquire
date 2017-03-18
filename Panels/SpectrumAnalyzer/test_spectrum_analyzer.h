#ifndef TEST_SPECTRUM_ANALYZER_H
#define TEST_SPECTRUM_ANALYZER_H

//C System-Headers
//
//C++ System headers
#include <memory>
//Qt Headers
#include <QTimer>
#include <QObject>
//OpenCV Headers
//
//Boost Headers
//
//Project specific headers
#include "Digitizer/ATS9462Engine/ats9462engine.h"
#include "../../Windows/mainwindow.h"
#include "spectrumanalyzer.h"

namespace etig {

namespace test {

class
TestSpectrumAnalyzer{

public:
    void Test();

private:
    MainWindow* w;
    SpectrumAnalyzer* spec;
    std::shared_ptr<ATS9462Engine> digitizer;

};

}

}

#endif // TEST_SPECTRUM_ANALYZER_H
