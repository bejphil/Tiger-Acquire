//C System-Headers
#include "test_spectrum_analyzer.h"
//C++ System headers
//
//Qt Headers
//
//OpenCV Headers
//
//Boost Headers
//
//Project specific headers
//

//#include "Digitizer/ATS9462/ats9462.cpp"
//#include "Digitizer/ATS9462Engine/ats9462engine.cpp"

namespace etig {

namespace test {

void TestSpectrumAnalyzer::Test() {

    w = new MainWindow();
    w->show();

    spec = new SpectrumAnalyzer( w );
    w -> SetSpectrumAnalyzerView( spec );

    QTimer* auto_timer = new QTimer( w );

//    digitizer = std::shared_ptr<ATS9462Engine>( new ATS9462Engine(2e6, 50, 50e6) );

//    digitizer->ThreadPoolSize( 10 );
//    digitizer->SetSampleRate( 2e6 );

//    digitizer->StartCapture();

//    QObject::connect( auto_timer, &QTimer::timeout, [=]() {
//        std::vector< float > volts_data = digitizer->PullVoltageDataTail( 1024 );
//        spec->UpdateSignal( volts_data, 2e6 );
//        std::cout << "Updated Signal ...? " << std::endl;
//    } );

//    sleep(1);
//    auto_timer->start( 33 );//timer refreshes every 500 ms

//    sleep( 1 );

//    while( true ) {
//        std::vector< float > volts_data = digitizer.PullVoltageDataTail( 1024 );
//        spec->UpdateSignal( volts_data, 2e6 );
//        sleep( 0.25 );
//    }

}

}

}
