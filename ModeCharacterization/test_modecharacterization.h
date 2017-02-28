#ifndef TEST_MODECHARACTERIZATION_H
#define TEST_MODECHARACTERIZATION_H


//C System-Headers
//
//C++ System headers
#include <vector>
#include <algorithm>
#include <functional>
//Qt Headers
//
//OpenCV Headers
//
//Boost Headers
//
//Project specific headers
#include "modecharacterization.h"

double volts_to_dbm( double voltage ) {
    return 20.0 * log10( voltage / std::sqrt(0.05) );
}

struct VoltsTodBm {

    void operator()(data_triple<double> &data) const {
        data.power_dBm = volts_to_dbm( data.power_dBm );
    }
};

inline double lorentzian( double f, double Q, double f_0 ) {
//    double gamma = frequency/( 2.0 * Q );

//    double num = gamma*gamma;
//    double denom = ( frequency - f_0 )*( frequency - f_0 ) + gamma*gamma;
    double fwhm = f_0/Q;
    double gamma = ( f_0 - f )/( fwhm/2.0 );

    return 1.0/( 1.0 + gamma*gamma );
}


void TestModeCharacterization() {

    const uint data_size = 10000;

    std::vector< data_triple<double> > test_data;
    test_data.reserve( data_size );

    double f_0 = 4000.0;
    double Q = 250.0;

    std::cout << "Testing mode characretizatipn.\n"
              << "Test mode has center frequency of "
              << f_0
              << " and Q of "
              << Q
              << std::endl;

    for( uint i = 0; i < data_size; i++ ) {

        double cavity_length = 0.0;
        double frequency = static_cast<double>( i );
        double power_dBm = 0.0025*lorentzian( frequency, Q, f_0 );

        test_data.push_back( data_triple<double>( cavity_length, frequency, power_dBm ) );

    }

    std::for_each( test_data.begin(), test_data.end(), VoltsTodBm() );

    ModeTraits characterization( test_data );

    double computed_Q = characterization.Q();
    double computed_f0 = characterization.f0();

    std::cout << "Computed mode parameters.\n"
              << "Center frequency of "
              << computed_f0
              << " and Q of "
              << computed_Q
              << std::endl;
}

#endif // TEST_MODECHARACTERIZATION_H
