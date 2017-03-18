//C System-Headers
#include "test_instrumentview.h"
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

namespace etig {

namespace test {

void TestInstrumentView::Test() {

    w = new MainWindow();
    w->show();

    na_view = new InstrumentView( w );
    w -> SetNetworkAnalyzerView( na_view );

    QTimer* auto_timer = new QTimer( w );

    const TCPSocketParam network_analyzer = TCPSocketParam( "NetworkAnalyzer", "10.95.100.176", 1234 );
    const uint nwa_points = 401;
    const double nwa_span_MHz = 400.0;
    const double nwa_power_dBm = -15.0;

    hp8757_c = std::shared_ptr<NetworkAnalyzer>( new NetworkAnalyzer( network_analyzer.ip_addr,\
               network_analyzer.port_addr,\
               nwa_points,\
               nwa_span_MHz,\
               nwa_power_dBm ) );

    std::cout << "Turning on RF source" << std::endl;
    hp8757_c->TurnOnRFSource();

    std::cout << "Setting frequency window to 1950 - 2050 MHz" << std::endl;
    hp8757_c->SetFrequencyWindow( 2000, 100 );

    QObject::connect( auto_timer, &QTimer::timeout, [=]() {

        std::cout << "Collecting single scan between 1950 - 2050 MHz" << std::endl;
        auto single_scan = hp8757_c->TakeDataSingle();

        na_view->UpdateSignal( single_scan, 100.0 );
        std::cout << "Updated Signal ...? " << std::endl;
    } );

    sleep(1);
    auto_timer->start( 33 );//timer refreshes every 500 ms

//    sleep( 1 );

//    while( true ) {
//        std::vector< float > volts_data = digitizer.PullVoltageDataTail( 1024 );
//        spec->UpdateSignal( volts_data, 2e6 );
//        sleep( 0.25 );
//    }

}

}

}
