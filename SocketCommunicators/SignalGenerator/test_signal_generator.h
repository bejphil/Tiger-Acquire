#ifndef TEST_SIGNAL_GENERATOR_H
#define TEST_SIGNAL_GENERATOR_H

//C System-Headers
//
//C++ System headers
#include <memory>
//Boost Headers
//
//Qt Headers
//
//Project specific headers
#include "signal_generator.h"
#include "../../Generics/generics.h"

void TestSignalGenerator() {

    std::cout << "Testing Signal Generator" << std::endl;

    const TCPSocketParam signal_generator = TCPSocketParam( "SignalGenerator", "10.95.100.175", 5025 );
    std::shared_ptr<SignalGenerator> mxg_n5183b = std::shared_ptr<SignalGenerator>( new SignalGenerator( signal_generator.ip_addr,\
                                                                        signal_generator.port_addr ) );

    const double freq_MHz = 15.0;
    const double power_dBm = -10.0;

    std::cout << "Turning RF power on." << std::endl;
    mxg_n5183b->RFOn();

    std::cout << "Turning RF power off." << std::endl;
    mxg_n5183b->RFOff();

    std::cout << "Turning RF power back on." << std::endl;
    mxg_n5183b->RFOn();

    std::cout << "Setting signal generator frequency to " << freq_MHz << " MHz." << std::endl;
    mxg_n5183b->SetFrequency( freq_MHz );

    std::cout << "Setting signal generator power to " << power_dBm << " dBm." << std::endl;
    mxg_n5183b->SetPower( power_dBm );

}

#endif // TEST_SIGNAL_GENERATOR_H
