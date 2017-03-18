#ifndef TEST_INSTRUMENTVIEW_H
#define TEST_INSTRUMENTVIEW_H

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
#include "../../SocketCommunicators/NetworkAnalyzer/network_analyzer.h"
#include "../../Windows/mainwindow.h"
#include "instrumentview.h"

namespace etig {

namespace test {

class
    TestInstrumentView {

  public:
    void Test();
  private:
    MainWindow* w;
    InstrumentView* na_view;
    std::shared_ptr<NetworkAnalyzer> hp8757_c;

};

}

}

#endif // TEST_INSTRUMENTVIEW_H
