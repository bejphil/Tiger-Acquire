#ifndef TEST_NETWORK_ANALYZER_H
#define TEST_NETWORK_ANALYZER_H

//C System-Headers
//
//C++ System headers
#include <memory>
//Boost Headers
//
//Qt Headers
//
// JASPL Headers
#include "../../../JASPL/jPlot/jplot.h"
//Project specific headers
#include "network_analyzer.h"
#include "../../Generics/generics.h"

template < typename T >
void print_vector( const std::vector<T>& vec ) {
    for( const auto& elem: vec ) {
        std::cout << elem << ",";
    }

    std::cout << std::endl;
}

void TestNetworkAnalyzer() {

    std::cout << "Testing Network Analyzer." << std::endl;

    const TCPSocketParam network_analyzer = TCPSocketParam( "NetworkAnalyzer", "10.95.100.176", 1234 );
    const uint nwa_points = 401;
    const double nwa_span_MHz = 400.0;
    const double nwa_power_dBm = -15.0;

    std::shared_ptr<NetworkAnalyzer> hp8757_c = \
            std::shared_ptr<NetworkAnalyzer>( new NetworkAnalyzer( network_analyzer.ip_addr,\
                    network_analyzer.port_addr,\
                    nwa_points,\
                    nwa_span_MHz,\
                    nwa_power_dBm ) );

    std::cout << "Turning on RF source" << std::endl;
    hp8757_c->TurnOnRFSource();

    std::cout << "Turning off RF source." << std::endl;
    hp8757_c->TurnOffRFSource();

    std::cout << "Turning RF source on again." << std::endl;
    hp8757_c->TurnOnRFSource();

    std::cout << "Setting frequency window to 1950 - 2050 MHz" << std::endl;
    hp8757_c->SetFrequencyWindow( 2000, 100 );

    std::cout << "Collecting single scan between 1950 - 2050 MHz" << std::endl;
    auto single_scan = hp8757_c->TakeDataSingle();
    jaspl::plot( single_scan );

    std::cout << "Collecting four scans ranging between 3000 - 4600 MHz" << std::endl;
    auto multiple_scan = hp8757_c->TakeDataMultiple();
    jaspl::plot( multiple_scan );

}

#endif // TEST_NETWORK_ANALYZER_H
