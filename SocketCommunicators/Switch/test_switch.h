#ifndef TEST_SWITCH_H
#define TEST_SWITCH_H


//C System-Headers
//
//C++ System headers
#include <memory>
//Boost Headers
//
//Qt Headers
//
//Project specific headers
#include "switch.h"
#include "../../Generics/generics.h"

void TestSwitch() {

    std::cout << "Testing Power Supply." << std::endl;

    const TCPSocketParam psu_switch = TCPSocketParam( "Switch", "10.95.100.174", 9221 );
    std::shared_ptr<Switch> xdl_35_5tp = std::shared_ptr<Switch>( new Switch( psu_switch.ip_addr,\
                                         psu_switch.port_addr ) );

    std::cout << "Switching to Network Analyzer" << std::endl;
    xdl_35_5tp->SwitchToNetworkAnalyzer();

    std::cout << "Switchig to Digitizer" << std::endl;
    xdl_35_5tp->SwitchToDigitizer();

    std::cout << "Switching to transmission measurements." << std::endl;
    xdl_35_5tp->SwitchToTransmission();
    std::cout << "Switching to reflection measurements." << std::endl;
    xdl_35_5tp->SwitchToReflection();

}

#endif // TEST_SWITCH_H
